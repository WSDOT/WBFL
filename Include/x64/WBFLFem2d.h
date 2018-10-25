

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:27:33 2017
 */
/* Compiler settings for ..\Include\WBFLFem2d.idl:
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


#ifndef __WBFLFem2d_h__
#define __WBFLFem2d_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFem2dEnumMemberID_FWD_DEFINED__
#define __IFem2dEnumMemberID_FWD_DEFINED__
typedef interface IFem2dEnumMemberID IFem2dEnumMemberID;

#endif 	/* __IFem2dEnumMemberID_FWD_DEFINED__ */


#ifndef __IFem2dJoint_FWD_DEFINED__
#define __IFem2dJoint_FWD_DEFINED__
typedef interface IFem2dJoint IFem2dJoint;

#endif 	/* __IFem2dJoint_FWD_DEFINED__ */


#ifndef __IFem2dEnumJoint_FWD_DEFINED__
#define __IFem2dEnumJoint_FWD_DEFINED__
typedef interface IFem2dEnumJoint IFem2dEnumJoint;

#endif 	/* __IFem2dEnumJoint_FWD_DEFINED__ */


#ifndef __IFem2dJointCollection_FWD_DEFINED__
#define __IFem2dJointCollection_FWD_DEFINED__
typedef interface IFem2dJointCollection IFem2dJointCollection;

#endif 	/* __IFem2dJointCollection_FWD_DEFINED__ */


#ifndef __IFem2dMember_FWD_DEFINED__
#define __IFem2dMember_FWD_DEFINED__
typedef interface IFem2dMember IFem2dMember;

#endif 	/* __IFem2dMember_FWD_DEFINED__ */


#ifndef __IFem2dEnumMember_FWD_DEFINED__
#define __IFem2dEnumMember_FWD_DEFINED__
typedef interface IFem2dEnumMember IFem2dEnumMember;

#endif 	/* __IFem2dEnumMember_FWD_DEFINED__ */


#ifndef __IFem2dMemberCollection_FWD_DEFINED__
#define __IFem2dMemberCollection_FWD_DEFINED__
typedef interface IFem2dMemberCollection IFem2dMemberCollection;

#endif 	/* __IFem2dMemberCollection_FWD_DEFINED__ */


#ifndef __IFem2dJointLoad_FWD_DEFINED__
#define __IFem2dJointLoad_FWD_DEFINED__
typedef interface IFem2dJointLoad IFem2dJointLoad;

#endif 	/* __IFem2dJointLoad_FWD_DEFINED__ */


#ifndef __IFem2dEnumJointLoad_FWD_DEFINED__
#define __IFem2dEnumJointLoad_FWD_DEFINED__
typedef interface IFem2dEnumJointLoad IFem2dEnumJointLoad;

#endif 	/* __IFem2dEnumJointLoad_FWD_DEFINED__ */


#ifndef __IFem2dJointLoadCollection_FWD_DEFINED__
#define __IFem2dJointLoadCollection_FWD_DEFINED__
typedef interface IFem2dJointLoadCollection IFem2dJointLoadCollection;

#endif 	/* __IFem2dJointLoadCollection_FWD_DEFINED__ */


#ifndef __IFem2dJointDeflection_FWD_DEFINED__
#define __IFem2dJointDeflection_FWD_DEFINED__
typedef interface IFem2dJointDeflection IFem2dJointDeflection;

#endif 	/* __IFem2dJointDeflection_FWD_DEFINED__ */


#ifndef __IFem2dEnumJointDeflection_FWD_DEFINED__
#define __IFem2dEnumJointDeflection_FWD_DEFINED__
typedef interface IFem2dEnumJointDeflection IFem2dEnumJointDeflection;

#endif 	/* __IFem2dEnumJointDeflection_FWD_DEFINED__ */


#ifndef __IFem2dJointDeflectionCollection_FWD_DEFINED__
#define __IFem2dJointDeflectionCollection_FWD_DEFINED__
typedef interface IFem2dJointDeflectionCollection IFem2dJointDeflectionCollection;

#endif 	/* __IFem2dJointDeflectionCollection_FWD_DEFINED__ */


#ifndef __IFem2dPointLoad_FWD_DEFINED__
#define __IFem2dPointLoad_FWD_DEFINED__
typedef interface IFem2dPointLoad IFem2dPointLoad;

#endif 	/* __IFem2dPointLoad_FWD_DEFINED__ */


#ifndef __IFem2dEnumPointLoad_FWD_DEFINED__
#define __IFem2dEnumPointLoad_FWD_DEFINED__
typedef interface IFem2dEnumPointLoad IFem2dEnumPointLoad;

#endif 	/* __IFem2dEnumPointLoad_FWD_DEFINED__ */


#ifndef __IFem2dPointLoadCollection_FWD_DEFINED__
#define __IFem2dPointLoadCollection_FWD_DEFINED__
typedef interface IFem2dPointLoadCollection IFem2dPointLoadCollection;

#endif 	/* __IFem2dPointLoadCollection_FWD_DEFINED__ */


#ifndef __IFem2dDistributedLoad_FWD_DEFINED__
#define __IFem2dDistributedLoad_FWD_DEFINED__
typedef interface IFem2dDistributedLoad IFem2dDistributedLoad;

#endif 	/* __IFem2dDistributedLoad_FWD_DEFINED__ */


#ifndef __IFem2dEnumDistributedLoad_FWD_DEFINED__
#define __IFem2dEnumDistributedLoad_FWD_DEFINED__
typedef interface IFem2dEnumDistributedLoad IFem2dEnumDistributedLoad;

#endif 	/* __IFem2dEnumDistributedLoad_FWD_DEFINED__ */


#ifndef __IFem2dDistributedLoadCollection_FWD_DEFINED__
#define __IFem2dDistributedLoadCollection_FWD_DEFINED__
typedef interface IFem2dDistributedLoadCollection IFem2dDistributedLoadCollection;

#endif 	/* __IFem2dDistributedLoadCollection_FWD_DEFINED__ */


#ifndef __IFem2dMemberStrain_FWD_DEFINED__
#define __IFem2dMemberStrain_FWD_DEFINED__
typedef interface IFem2dMemberStrain IFem2dMemberStrain;

#endif 	/* __IFem2dMemberStrain_FWD_DEFINED__ */


#ifndef __IFem2dEnumMemberStrain_FWD_DEFINED__
#define __IFem2dEnumMemberStrain_FWD_DEFINED__
typedef interface IFem2dEnumMemberStrain IFem2dEnumMemberStrain;

#endif 	/* __IFem2dEnumMemberStrain_FWD_DEFINED__ */


#ifndef __IFem2dMemberStrainCollection_FWD_DEFINED__
#define __IFem2dMemberStrainCollection_FWD_DEFINED__
typedef interface IFem2dMemberStrainCollection IFem2dMemberStrainCollection;

#endif 	/* __IFem2dMemberStrainCollection_FWD_DEFINED__ */


#ifndef __IFem2dLoading_FWD_DEFINED__
#define __IFem2dLoading_FWD_DEFINED__
typedef interface IFem2dLoading IFem2dLoading;

#endif 	/* __IFem2dLoading_FWD_DEFINED__ */


#ifndef __IFem2dEnumLoading_FWD_DEFINED__
#define __IFem2dEnumLoading_FWD_DEFINED__
typedef interface IFem2dEnumLoading IFem2dEnumLoading;

#endif 	/* __IFem2dEnumLoading_FWD_DEFINED__ */


#ifndef __IFem2dLoadingCollection_FWD_DEFINED__
#define __IFem2dLoadingCollection_FWD_DEFINED__
typedef interface IFem2dLoadingCollection IFem2dLoadingCollection;

#endif 	/* __IFem2dLoadingCollection_FWD_DEFINED__ */


#ifndef __IFem2dPOI_FWD_DEFINED__
#define __IFem2dPOI_FWD_DEFINED__
typedef interface IFem2dPOI IFem2dPOI;

#endif 	/* __IFem2dPOI_FWD_DEFINED__ */


#ifndef __IFem2dEnumPOI_FWD_DEFINED__
#define __IFem2dEnumPOI_FWD_DEFINED__
typedef interface IFem2dEnumPOI IFem2dEnumPOI;

#endif 	/* __IFem2dEnumPOI_FWD_DEFINED__ */


#ifndef __IFem2dPOICollection_FWD_DEFINED__
#define __IFem2dPOICollection_FWD_DEFINED__
typedef interface IFem2dPOICollection IFem2dPOICollection;

#endif 	/* __IFem2dPOICollection_FWD_DEFINED__ */


#ifndef __IFem2dModelResults_FWD_DEFINED__
#define __IFem2dModelResults_FWD_DEFINED__
typedef interface IFem2dModelResults IFem2dModelResults;

#endif 	/* __IFem2dModelResults_FWD_DEFINED__ */


#ifndef __IFem2dModelResultsEx_FWD_DEFINED__
#define __IFem2dModelResultsEx_FWD_DEFINED__
typedef interface IFem2dModelResultsEx IFem2dModelResultsEx;

#endif 	/* __IFem2dModelResultsEx_FWD_DEFINED__ */


#ifndef __IFem2dModelResultsForScriptingClients_FWD_DEFINED__
#define __IFem2dModelResultsForScriptingClients_FWD_DEFINED__
typedef interface IFem2dModelResultsForScriptingClients IFem2dModelResultsForScriptingClients;

#endif 	/* __IFem2dModelResultsForScriptingClients_FWD_DEFINED__ */


#ifndef __IFem2dModel_FWD_DEFINED__
#define __IFem2dModel_FWD_DEFINED__
typedef interface IFem2dModel IFem2dModel;

#endif 	/* __IFem2dModel_FWD_DEFINED__ */


#ifndef __IFem2dModelEvents_FWD_DEFINED__
#define __IFem2dModelEvents_FWD_DEFINED__
typedef interface IFem2dModelEvents IFem2dModelEvents;

#endif 	/* __IFem2dModelEvents_FWD_DEFINED__ */


#ifndef __Fem2dModel_FWD_DEFINED__
#define __Fem2dModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dModel Fem2dModel;
#else
typedef struct Fem2dModel Fem2dModel;
#endif /* __cplusplus */

#endif 	/* __Fem2dModel_FWD_DEFINED__ */


#ifndef __Fem2dJointCollection_FWD_DEFINED__
#define __Fem2dJointCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJointCollection Fem2dJointCollection;
#else
typedef struct Fem2dJointCollection Fem2dJointCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dJointCollection_FWD_DEFINED__ */


#ifndef __Fem2dJoint_FWD_DEFINED__
#define __Fem2dJoint_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJoint Fem2dJoint;
#else
typedef struct Fem2dJoint Fem2dJoint;
#endif /* __cplusplus */

#endif 	/* __Fem2dJoint_FWD_DEFINED__ */


#ifndef __Fem2dMember_FWD_DEFINED__
#define __Fem2dMember_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dMember Fem2dMember;
#else
typedef struct Fem2dMember Fem2dMember;
#endif /* __cplusplus */

#endif 	/* __Fem2dMember_FWD_DEFINED__ */


#ifndef __Fem2dMemberCollection_FWD_DEFINED__
#define __Fem2dMemberCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dMemberCollection Fem2dMemberCollection;
#else
typedef struct Fem2dMemberCollection Fem2dMemberCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dMemberCollection_FWD_DEFINED__ */


#ifndef __Fem2dJointLoad_FWD_DEFINED__
#define __Fem2dJointLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJointLoad Fem2dJointLoad;
#else
typedef struct Fem2dJointLoad Fem2dJointLoad;
#endif /* __cplusplus */

#endif 	/* __Fem2dJointLoad_FWD_DEFINED__ */


#ifndef __Fem2dJointLoadCollection_FWD_DEFINED__
#define __Fem2dJointLoadCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJointLoadCollection Fem2dJointLoadCollection;
#else
typedef struct Fem2dJointLoadCollection Fem2dJointLoadCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dJointLoadCollection_FWD_DEFINED__ */


#ifndef __Fem2dJointDeflection_FWD_DEFINED__
#define __Fem2dJointDeflection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJointDeflection Fem2dJointDeflection;
#else
typedef struct Fem2dJointDeflection Fem2dJointDeflection;
#endif /* __cplusplus */

#endif 	/* __Fem2dJointDeflection_FWD_DEFINED__ */


#ifndef __Fem2dJointDeflectionCollection_FWD_DEFINED__
#define __Fem2dJointDeflectionCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dJointDeflectionCollection Fem2dJointDeflectionCollection;
#else
typedef struct Fem2dJointDeflectionCollection Fem2dJointDeflectionCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dJointDeflectionCollection_FWD_DEFINED__ */


#ifndef __Fem2dMemberStrain_FWD_DEFINED__
#define __Fem2dMemberStrain_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dMemberStrain Fem2dMemberStrain;
#else
typedef struct Fem2dMemberStrain Fem2dMemberStrain;
#endif /* __cplusplus */

#endif 	/* __Fem2dMemberStrain_FWD_DEFINED__ */


#ifndef __Fem2dMemberStrainCollection_FWD_DEFINED__
#define __Fem2dMemberStrainCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dMemberStrainCollection Fem2dMemberStrainCollection;
#else
typedef struct Fem2dMemberStrainCollection Fem2dMemberStrainCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dMemberStrainCollection_FWD_DEFINED__ */


#ifndef __Fem2dLoading_FWD_DEFINED__
#define __Fem2dLoading_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dLoading Fem2dLoading;
#else
typedef struct Fem2dLoading Fem2dLoading;
#endif /* __cplusplus */

#endif 	/* __Fem2dLoading_FWD_DEFINED__ */


#ifndef __Fem2dLoadingCollection_FWD_DEFINED__
#define __Fem2dLoadingCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dLoadingCollection Fem2dLoadingCollection;
#else
typedef struct Fem2dLoadingCollection Fem2dLoadingCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dLoadingCollection_FWD_DEFINED__ */


#ifndef __Fem2dPointLoad_FWD_DEFINED__
#define __Fem2dPointLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dPointLoad Fem2dPointLoad;
#else
typedef struct Fem2dPointLoad Fem2dPointLoad;
#endif /* __cplusplus */

#endif 	/* __Fem2dPointLoad_FWD_DEFINED__ */


#ifndef __Fem2dPointLoadCollection_FWD_DEFINED__
#define __Fem2dPointLoadCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dPointLoadCollection Fem2dPointLoadCollection;
#else
typedef struct Fem2dPointLoadCollection Fem2dPointLoadCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dPointLoadCollection_FWD_DEFINED__ */


#ifndef __Fem2dDistributedLoad_FWD_DEFINED__
#define __Fem2dDistributedLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dDistributedLoad Fem2dDistributedLoad;
#else
typedef struct Fem2dDistributedLoad Fem2dDistributedLoad;
#endif /* __cplusplus */

#endif 	/* __Fem2dDistributedLoad_FWD_DEFINED__ */


#ifndef __Fem2dDistributedLoadCollection_FWD_DEFINED__
#define __Fem2dDistributedLoadCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dDistributedLoadCollection Fem2dDistributedLoadCollection;
#else
typedef struct Fem2dDistributedLoadCollection Fem2dDistributedLoadCollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dDistributedLoadCollection_FWD_DEFINED__ */


#ifndef __Fem2dPOI_FWD_DEFINED__
#define __Fem2dPOI_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dPOI Fem2dPOI;
#else
typedef struct Fem2dPOI Fem2dPOI;
#endif /* __cplusplus */

#endif 	/* __Fem2dPOI_FWD_DEFINED__ */


#ifndef __Fem2dPOICollection_FWD_DEFINED__
#define __Fem2dPOICollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class Fem2dPOICollection Fem2dPOICollection;
#else
typedef struct Fem2dPOICollection Fem2dPOICollection;
#endif /* __cplusplus */

#endif 	/* __Fem2dPOICollection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLFem2d_0000_0000 */
/* [local] */ 

#include "Fem2dErrors.h"


extern RPC_IF_HANDLE __MIDL_itf_WBFLFem2d_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLFem2d_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLFem2d_LIBRARY_DEFINED__
#define __WBFLFem2d_LIBRARY_DEFINED__

/* library WBFLFem2d */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [public][public][public][public][public][public][public][public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("FABE04A0-FF96-11d2-8CDF-F43C3928A334") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0001
    {
        atIndex	= 0,
        atID	= 1
    } 	Fem2dAccessType;

typedef /* [public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("6D99D3D9-B9BC-11d4-AF44-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0002
    {
        mbrReleaseNone	= 0,
        mbrReleaseMz	= 1,
        mbrReleaseFx	= 2
    } 	Fem2dMbrReleaseType;

typedef /* [public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("3B343406-B05C-11d4-AF39-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0003
    {
        metStart	= 0,
        metEnd	= 1
    } 	Fem2dMbrEndType;

typedef /* [public][public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("40ABF188-B112-11d4-AF3A-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0004
    {
        jrtNone	= 0,
        jrtFx	= 1,
        jrtFy	= 2,
        jrtMz	= 4,
        jrtAll	= 7
    } 	Fem2dJointReleaseType;

typedef /* [public][public][public][public][public][public][public][public][public][public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("CA256DDA-BB27-11d4-AF47-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0005
    {
        lotGlobal	= 0,
        lotMember	= 1,
        lotGlobalProjected	= 2
    } 	Fem2dLoadOrientation;

typedef /* [public][public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("6B8719C5-D774-11d4-AF64-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0006
    {
        loadDirFx	= 0,
        loadDirFy	= 1
    } 	Fem2dLoadDirection;

typedef /* [public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("12033448-C0DC-11d4-AF4C-00105A9AF985") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0007
    {
        mftLeft	= 0,
        mftRight	= 1
    } 	Fem2dMbrFaceType;

typedef /* [public][public][public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("DB3A3C38-082D-11d5-8BB9-006097C68A9C") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0008
    {
        jdofDx	= 0,
        jdofDy	= 1,
        jdofRz	= 2
    } 	Fem2dJointDOF;

typedef /* [public][public][public][helpstring][helpcontext][uuid][public] */  DECLSPEC_UUID("DB3A3C39-082D-11d5-8BB9-006097C68A9C") 
enum __MIDL___MIDL_itf_WBFLFem2d_0000_0000_0009
    {
        mdofDxStart	= 0,
        mdofDyStart	= 1,
        mdofRzStart	= 2,
        mdofDxEnd	= 3,
        mdofDyEnd	= 4,
        mdofRzEnd	= 5
    } 	Fem2dMbrDOF;


EXTERN_C const IID LIBID_WBFLFem2d;

#ifndef __IFem2dEnumMemberID_INTERFACE_DEFINED__
#define __IFem2dEnumMemberID_INTERFACE_DEFINED__

/* interface IFem2dEnumMemberID */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumMemberID;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FFA6147B-F3E7-11d4-AF82-00105A9AF985")
    IFem2dEnumMemberID : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumMemberID **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ MemberIDType *rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumMemberIDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumMemberID * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumMemberID * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumMemberID * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumMemberID * This,
            /* [out] */ IFem2dEnumMemberID **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumMemberID * This,
            /* [in] */ ULONG celt,
            /* [out] */ MemberIDType *rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumMemberID * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumMemberID * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumMemberIDVtbl;

    interface IFem2dEnumMemberID
    {
        CONST_VTBL struct IFem2dEnumMemberIDVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumMemberID_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumMemberID_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumMemberID_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumMemberID_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumMemberID_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumMemberID_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumMemberID_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumMemberID_INTERFACE_DEFINED__ */


#ifndef __IFem2dJoint_INTERFACE_DEFINED__
#define __IFem2dJoint_INTERFACE_DEFINED__

/* interface IFem2dJoint */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("807A623A-AE89-11D4-AF38-00105A9AF985")
    IFem2dJoint : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ JointIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE IsDofReleased( 
            /* [in] */ Fem2dJointReleaseType rel,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE IsSupport( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Support( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Free( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReleaseDof( 
            /* [in] */ Fem2dJointReleaseType rel) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE IsDofSupported( 
            /* [in] */ Fem2dJointReleaseType rel,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ IIDArray **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJoint * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dJoint * This,
            /* [retval][out] */ JointIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IFem2dJoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IFem2dJoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IFem2dJoint * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IFem2dJoint * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *IsDofReleased )( 
            IFem2dJoint * This,
            /* [in] */ Fem2dJointReleaseType rel,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *IsSupport )( 
            IFem2dJoint * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Support )( 
            IFem2dJoint * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Free )( 
            IFem2dJoint * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReleaseDof )( 
            IFem2dJoint * This,
            /* [in] */ Fem2dJointReleaseType rel);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *IsDofSupported )( 
            IFem2dJoint * This,
            /* [in] */ Fem2dJointReleaseType rel,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Members )( 
            IFem2dJoint * This,
            /* [retval][out] */ IIDArray **pVal);
        
        END_INTERFACE
    } IFem2dJointVtbl;

    interface IFem2dJoint
    {
        CONST_VTBL struct IFem2dJointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJoint_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dJoint_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IFem2dJoint_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IFem2dJoint_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IFem2dJoint_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IFem2dJoint_IsDofReleased(This,rel,pVal)	\
    ( (This)->lpVtbl -> IsDofReleased(This,rel,pVal) ) 

#define IFem2dJoint_IsSupport(This,pVal)	\
    ( (This)->lpVtbl -> IsSupport(This,pVal) ) 

#define IFem2dJoint_Support(This)	\
    ( (This)->lpVtbl -> Support(This) ) 

#define IFem2dJoint_Free(This)	\
    ( (This)->lpVtbl -> Free(This) ) 

#define IFem2dJoint_ReleaseDof(This,rel)	\
    ( (This)->lpVtbl -> ReleaseDof(This,rel) ) 

#define IFem2dJoint_IsDofSupported(This,rel,pVal)	\
    ( (This)->lpVtbl -> IsDofSupported(This,rel,pVal) ) 

#define IFem2dJoint_get_Members(This,pVal)	\
    ( (This)->lpVtbl -> get_Members(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJoint_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumJoint_INTERFACE_DEFINED__
#define __IFem2dEnumJoint_INTERFACE_DEFINED__

/* interface IFem2dEnumJoint */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumJoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A9136294-B01B-11d4-AF39-00105A9AF985")
    IFem2dEnumJoint : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumJoint **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumJointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumJoint * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumJoint * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumJoint * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumJoint * This,
            /* [out] */ IFem2dEnumJoint **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumJoint * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJoint **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumJoint * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumJoint * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumJointVtbl;

    interface IFem2dEnumJoint
    {
        CONST_VTBL struct IFem2dEnumJointVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumJoint_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumJoint_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumJoint_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumJoint_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumJoint_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumJoint_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumJoint_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumJoint_INTERFACE_DEFINED__ */


#ifndef __IFem2dJointCollection_INTERFACE_DEFINED__
#define __IFem2dJointCollection_INTERFACE_DEFINED__

/* interface IFem2dJointCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJointCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("807A6238-AE89-11D4-AF38-00105A9AF985")
    IFem2dJointCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJoint **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumJoint **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ JointIDType ID,
            /* [retval][out] */ IFem2dJoint **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ JointIDType ID,
            /* [in] */ Float64 fltX,
            /* [in] */ Float64 fltY,
            /* [retval][out] */ IFem2dJoint **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ JointIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJointCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJointCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJointCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dJointCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJoint **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dJointCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dJointCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dJointCollection * This,
            /* [retval][out] */ IFem2dEnumJoint **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dJointCollection * This,
            /* [in] */ JointIDType ID,
            /* [retval][out] */ IFem2dJoint **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dJointCollection * This,
            /* [in] */ JointIDType ID,
            /* [in] */ Float64 fltX,
            /* [in] */ Float64 fltY,
            /* [retval][out] */ IFem2dJoint **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dJointCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ JointIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dJointCollection * This);
        
        END_INTERFACE
    } IFem2dJointCollectionVtbl;

    interface IFem2dJointCollection
    {
        CONST_VTBL struct IFem2dJointCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJointCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJointCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJointCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJointCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dJointCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dJointCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dJointCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dJointCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dJointCollection_Create(This,ID,fltX,fltY,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,fltX,fltY,pVal) ) 

#define IFem2dJointCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dJointCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJointCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dMember_INTERFACE_DEFINED__
#define __IFem2dMember_INTERFACE_DEFINED__

/* interface IFem2dMember */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BA5C1A5-B009-11D4-AF39-00105A9AF985")
    IFem2dMember : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StartJoint( 
            /* [retval][out] */ JointIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_StartJoint( 
            /* [in] */ JointIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EndJoint( 
            /* [retval][out] */ JointIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE IsReleased( 
            /* [in] */ Fem2dMbrEndType end,
            /* [in] */ Fem2dMbrReleaseType releaseType,
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ReleaseEnd( 
            /* [in] */ Fem2dMbrEndType whichEnd,
            /* [in] */ Fem2dMbrReleaseType releaseType) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_EndJoint( 
            /* [in] */ JointIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EA( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_EA( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EI( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_EI( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dMember * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dMember * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dMember * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dMember * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartJoint )( 
            IFem2dMember * This,
            /* [retval][out] */ JointIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartJoint )( 
            IFem2dMember * This,
            /* [in] */ JointIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndJoint )( 
            IFem2dMember * This,
            /* [retval][out] */ JointIDType *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *IsReleased )( 
            IFem2dMember * This,
            /* [in] */ Fem2dMbrEndType end,
            /* [in] */ Fem2dMbrReleaseType releaseType,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ReleaseEnd )( 
            IFem2dMember * This,
            /* [in] */ Fem2dMbrEndType whichEnd,
            /* [in] */ Fem2dMbrReleaseType releaseType);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndJoint )( 
            IFem2dMember * This,
            /* [in] */ JointIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EA )( 
            IFem2dMember * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EA )( 
            IFem2dMember * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EI )( 
            IFem2dMember * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EI )( 
            IFem2dMember * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IFem2dMember * This,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IFem2dMemberVtbl;

    interface IFem2dMember
    {
        CONST_VTBL struct IFem2dMemberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dMember_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dMember_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dMember_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dMember_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dMember_get_StartJoint(This,pVal)	\
    ( (This)->lpVtbl -> get_StartJoint(This,pVal) ) 

#define IFem2dMember_put_StartJoint(This,newVal)	\
    ( (This)->lpVtbl -> put_StartJoint(This,newVal) ) 

#define IFem2dMember_get_EndJoint(This,pVal)	\
    ( (This)->lpVtbl -> get_EndJoint(This,pVal) ) 

#define IFem2dMember_IsReleased(This,end,releaseType,pVal)	\
    ( (This)->lpVtbl -> IsReleased(This,end,releaseType,pVal) ) 

#define IFem2dMember_ReleaseEnd(This,whichEnd,releaseType)	\
    ( (This)->lpVtbl -> ReleaseEnd(This,whichEnd,releaseType) ) 

#define IFem2dMember_put_EndJoint(This,newVal)	\
    ( (This)->lpVtbl -> put_EndJoint(This,newVal) ) 

#define IFem2dMember_get_EA(This,pVal)	\
    ( (This)->lpVtbl -> get_EA(This,pVal) ) 

#define IFem2dMember_put_EA(This,newVal)	\
    ( (This)->lpVtbl -> put_EA(This,newVal) ) 

#define IFem2dMember_get_EI(This,pVal)	\
    ( (This)->lpVtbl -> get_EI(This,pVal) ) 

#define IFem2dMember_put_EI(This,newVal)	\
    ( (This)->lpVtbl -> put_EI(This,newVal) ) 

#define IFem2dMember_get_Length(This,pVal)	\
    ( (This)->lpVtbl -> get_Length(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dMember_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumMember_INTERFACE_DEFINED__
#define __IFem2dEnumMember_INTERFACE_DEFINED__

/* interface IFem2dEnumMember */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumMember;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6ADC094-B057-11d4-AF39-00105A9AF985")
    IFem2dEnumMember : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumMember **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumMemberVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumMember * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumMember * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumMember * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumMember * This,
            /* [out] */ IFem2dEnumMember **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumMember * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dMember **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumMember * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumMember * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumMemberVtbl;

    interface IFem2dEnumMember
    {
        CONST_VTBL struct IFem2dEnumMemberVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumMember_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumMember_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumMember_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumMember_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumMember_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumMember_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumMember_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumMember_INTERFACE_DEFINED__ */


#ifndef __IFem2dMemberCollection_INTERFACE_DEFINED__
#define __IFem2dMemberCollection_INTERFACE_DEFINED__

/* interface IFem2dMemberCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dMemberCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6ADC095-B057-11d4-AF39-00105A9AF985")
    IFem2dMemberCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dMember **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumMember **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ MemberIDType ID,
            /* [retval][out] */ IFem2dMember **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ MemberIDType ID,
            /* [in] */ JointIDType startJoint,
            /* [in] */ JointIDType EndJoint,
            /* [in] */ Float64 EA,
            /* [in] */ Float64 EI,
            /* [retval][out] */ IFem2dMember **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ MemberIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dMemberCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dMemberCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dMemberCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dMemberCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dMemberCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dMember **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dMemberCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dMemberCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dMemberCollection * This,
            /* [retval][out] */ IFem2dEnumMember **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dMemberCollection * This,
            /* [in] */ MemberIDType ID,
            /* [retval][out] */ IFem2dMember **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dMemberCollection * This,
            /* [in] */ MemberIDType ID,
            /* [in] */ JointIDType startJoint,
            /* [in] */ JointIDType EndJoint,
            /* [in] */ Float64 EA,
            /* [in] */ Float64 EI,
            /* [retval][out] */ IFem2dMember **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dMemberCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ MemberIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dMemberCollection * This);
        
        END_INTERFACE
    } IFem2dMemberCollectionVtbl;

    interface IFem2dMemberCollection
    {
        CONST_VTBL struct IFem2dMemberCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dMemberCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dMemberCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dMemberCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dMemberCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dMemberCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dMemberCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dMemberCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dMemberCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dMemberCollection_Create(This,ID,startJoint,EndJoint,EA,EI,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,startJoint,EndJoint,EA,EI,pVal) ) 

#define IFem2dMemberCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dMemberCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dMemberCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dJointLoad_INTERFACE_DEFINED__
#define __IFem2dJointLoad_INTERFACE_DEFINED__

/* interface IFem2dJointLoad */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("820F7F26-BA41-11D4-AF46-00105A9AF985")
    IFem2dJointLoad : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_JointID( 
            /* [retval][out] */ JointIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_JointID( 
            /* [in] */ JointIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Fx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Mz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE SetForce( 
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetForce( 
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loading( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJointLoad * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JointID )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ JointIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JointID )( 
            IFem2dJointLoad * This,
            /* [in] */ JointIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fx )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fx )( 
            IFem2dJointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fy )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fy )( 
            IFem2dJointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mz )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mz )( 
            IFem2dJointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *SetForce )( 
            IFem2dJointLoad * This,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetForce )( 
            IFem2dJointLoad * This,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loading )( 
            IFem2dJointLoad * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        END_INTERFACE
    } IFem2dJointLoadVtbl;

    interface IFem2dJointLoad
    {
        CONST_VTBL struct IFem2dJointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJointLoad_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dJointLoad_get_JointID(This,pVal)	\
    ( (This)->lpVtbl -> get_JointID(This,pVal) ) 

#define IFem2dJointLoad_put_JointID(This,newVal)	\
    ( (This)->lpVtbl -> put_JointID(This,newVal) ) 

#define IFem2dJointLoad_get_Fx(This,pVal)	\
    ( (This)->lpVtbl -> get_Fx(This,pVal) ) 

#define IFem2dJointLoad_put_Fx(This,newVal)	\
    ( (This)->lpVtbl -> put_Fx(This,newVal) ) 

#define IFem2dJointLoad_get_Fy(This,pVal)	\
    ( (This)->lpVtbl -> get_Fy(This,pVal) ) 

#define IFem2dJointLoad_put_Fy(This,newVal)	\
    ( (This)->lpVtbl -> put_Fy(This,newVal) ) 

#define IFem2dJointLoad_get_Mz(This,pVal)	\
    ( (This)->lpVtbl -> get_Mz(This,pVal) ) 

#define IFem2dJointLoad_put_Mz(This,newVal)	\
    ( (This)->lpVtbl -> put_Mz(This,newVal) ) 

#define IFem2dJointLoad_SetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> SetForce(This,Fx,Fy,Mz) ) 

#define IFem2dJointLoad_GetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> GetForce(This,Fx,Fy,Mz) ) 

#define IFem2dJointLoad_get_Loading(This,pVal)	\
    ( (This)->lpVtbl -> get_Loading(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJointLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumJointLoad_INTERFACE_DEFINED__
#define __IFem2dEnumJointLoad_INTERFACE_DEFINED__

/* interface IFem2dEnumJointLoad */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumJointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6DEA0F48-BA83-11d4-AF46-00105A9AF985")
    IFem2dEnumJointLoad : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumJointLoad **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJointLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumJointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumJointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumJointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumJointLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumJointLoad * This,
            /* [out] */ IFem2dEnumJointLoad **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumJointLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJointLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumJointLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumJointLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumJointLoadVtbl;

    interface IFem2dEnumJointLoad
    {
        CONST_VTBL struct IFem2dEnumJointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumJointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumJointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumJointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumJointLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumJointLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumJointLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumJointLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumJointLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dJointLoadCollection_INTERFACE_DEFINED__
#define __IFem2dJointLoadCollection_INTERFACE_DEFINED__

/* interface IFem2dJointLoadCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJointLoadCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("820F7F28-BA41-11D4-AF46-00105A9AF985")
    IFem2dJointLoadCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJointLoad **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumJointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dJointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadIDType ID,
            /* [in] */ JointIDType joint,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz,
            /* [retval][out] */ IFem2dJointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointLoadCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJointLoadCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJointLoadCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJointLoadCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dJointLoadCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJointLoad **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dJointLoadCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dJointLoadCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dJointLoadCollection * This,
            /* [retval][out] */ IFem2dEnumJointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dJointLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dJointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dJointLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ JointIDType joint,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz,
            /* [retval][out] */ IFem2dJointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dJointLoadCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dJointLoadCollection * This);
        
        END_INTERFACE
    } IFem2dJointLoadCollectionVtbl;

    interface IFem2dJointLoadCollection
    {
        CONST_VTBL struct IFem2dJointLoadCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJointLoadCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJointLoadCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJointLoadCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJointLoadCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dJointLoadCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dJointLoadCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dJointLoadCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dJointLoadCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dJointLoadCollection_Create(This,ID,joint,Fx,Fy,Mz,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,joint,Fx,Fy,Mz,pVal) ) 

#define IFem2dJointLoadCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dJointLoadCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJointLoadCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dJointDeflection_INTERFACE_DEFINED__
#define __IFem2dJointDeflection_INTERFACE_DEFINED__

/* interface IFem2dJointDeflection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJointDeflection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5642476-CFBF-11d4-AF5D-00105A9AF985")
    IFem2dJointDeflection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_JointID( 
            /* [retval][out] */ JointIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_JointID( 
            /* [in] */ JointIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Dx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Dx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Dy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Dy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Rz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Rz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE SetDeflection( 
            /* [in] */ Float64 Dx,
            /* [in] */ Float64 Dy,
            /* [in] */ Float64 Rz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetDeflection( 
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loading( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointDeflectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJointDeflection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJointDeflection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJointDeflection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JointID )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ JointIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_JointID )( 
            IFem2dJointDeflection * This,
            /* [in] */ JointIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dx )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dx )( 
            IFem2dJointDeflection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dy )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dy )( 
            IFem2dJointDeflection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rz )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rz )( 
            IFem2dJointDeflection * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *SetDeflection )( 
            IFem2dJointDeflection * This,
            /* [in] */ Float64 Dx,
            /* [in] */ Float64 Dy,
            /* [in] */ Float64 Rz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetDeflection )( 
            IFem2dJointDeflection * This,
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loading )( 
            IFem2dJointDeflection * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        END_INTERFACE
    } IFem2dJointDeflectionVtbl;

    interface IFem2dJointDeflection
    {
        CONST_VTBL struct IFem2dJointDeflectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJointDeflection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJointDeflection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJointDeflection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJointDeflection_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dJointDeflection_get_JointID(This,pVal)	\
    ( (This)->lpVtbl -> get_JointID(This,pVal) ) 

#define IFem2dJointDeflection_put_JointID(This,newVal)	\
    ( (This)->lpVtbl -> put_JointID(This,newVal) ) 

#define IFem2dJointDeflection_get_Dx(This,pVal)	\
    ( (This)->lpVtbl -> get_Dx(This,pVal) ) 

#define IFem2dJointDeflection_put_Dx(This,newVal)	\
    ( (This)->lpVtbl -> put_Dx(This,newVal) ) 

#define IFem2dJointDeflection_get_Dy(This,pVal)	\
    ( (This)->lpVtbl -> get_Dy(This,pVal) ) 

#define IFem2dJointDeflection_put_Dy(This,newVal)	\
    ( (This)->lpVtbl -> put_Dy(This,newVal) ) 

#define IFem2dJointDeflection_get_Rz(This,pVal)	\
    ( (This)->lpVtbl -> get_Rz(This,pVal) ) 

#define IFem2dJointDeflection_put_Rz(This,newVal)	\
    ( (This)->lpVtbl -> put_Rz(This,newVal) ) 

#define IFem2dJointDeflection_SetDeflection(This,Dx,Dy,Rz)	\
    ( (This)->lpVtbl -> SetDeflection(This,Dx,Dy,Rz) ) 

#define IFem2dJointDeflection_GetDeflection(This,Dx,Dy,Rz)	\
    ( (This)->lpVtbl -> GetDeflection(This,Dx,Dy,Rz) ) 

#define IFem2dJointDeflection_get_Loading(This,pVal)	\
    ( (This)->lpVtbl -> get_Loading(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJointDeflection_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumJointDeflection_INTERFACE_DEFINED__
#define __IFem2dEnumJointDeflection_INTERFACE_DEFINED__

/* interface IFem2dEnumJointDeflection */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumJointDeflection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5642477-CFBF-11d4-AF5D-00105A9AF985")
    IFem2dEnumJointDeflection : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumJointDeflection **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJointDeflection **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumJointDeflectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumJointDeflection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumJointDeflection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumJointDeflection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumJointDeflection * This,
            /* [out] */ IFem2dEnumJointDeflection **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumJointDeflection * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dJointDeflection **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumJointDeflection * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumJointDeflection * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumJointDeflectionVtbl;

    interface IFem2dEnumJointDeflection
    {
        CONST_VTBL struct IFem2dEnumJointDeflectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumJointDeflection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumJointDeflection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumJointDeflection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumJointDeflection_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumJointDeflection_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumJointDeflection_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumJointDeflection_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumJointDeflection_INTERFACE_DEFINED__ */


#ifndef __IFem2dJointDeflectionCollection_INTERFACE_DEFINED__
#define __IFem2dJointDeflectionCollection_INTERFACE_DEFINED__

/* interface IFem2dJointDeflectionCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dJointDeflectionCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5642478-CFBF-11d4-AF5D-00105A9AF985")
    IFem2dJointDeflectionCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJointDeflection **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumJointDeflection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dJointDeflection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadIDType ID,
            /* [in] */ JointIDType joint,
            /* [in] */ Float64 Dx,
            /* [in] */ Float64 Dy,
            /* [in] */ Float64 Rz,
            /* [retval][out] */ IFem2dJointDeflection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dJointDeflectionCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dJointDeflectionCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dJointDeflectionCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dJointDeflectionCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dJointDeflectionCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dJointDeflection **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dJointDeflectionCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dJointDeflectionCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dJointDeflectionCollection * This,
            /* [retval][out] */ IFem2dEnumJointDeflection **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dJointDeflectionCollection * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dJointDeflection **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dJointDeflectionCollection * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ JointIDType joint,
            /* [in] */ Float64 Dx,
            /* [in] */ Float64 Dy,
            /* [in] */ Float64 Rz,
            /* [retval][out] */ IFem2dJointDeflection **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dJointDeflectionCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dJointDeflectionCollection * This);
        
        END_INTERFACE
    } IFem2dJointDeflectionCollectionVtbl;

    interface IFem2dJointDeflectionCollection
    {
        CONST_VTBL struct IFem2dJointDeflectionCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dJointDeflectionCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dJointDeflectionCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dJointDeflectionCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dJointDeflectionCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dJointDeflectionCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dJointDeflectionCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dJointDeflectionCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dJointDeflectionCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dJointDeflectionCollection_Create(This,ID,joint,Dx,Dy,Rz,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,joint,Dx,Dy,Rz,pVal) ) 

#define IFem2dJointDeflectionCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dJointDeflectionCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dJointDeflectionCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dPointLoad_INTERFACE_DEFINED__
#define __IFem2dPointLoad_INTERFACE_DEFINED__

/* interface IFem2dPointLoad */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("50D65B03-BB0D-11D4-AF47-00105A9AF985")
    IFem2dPointLoad : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ Fem2dLoadOrientation *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ Fem2dLoadOrientation newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Fx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Mz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE SetForce( 
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE GetForce( 
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loading( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dPointLoad * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IFem2dPointLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ Fem2dLoadOrientation *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IFem2dPointLoad * This,
            /* [in] */ Fem2dLoadOrientation newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fx )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fx )( 
            IFem2dPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fy )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fy )( 
            IFem2dPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mz )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mz )( 
            IFem2dPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *SetForce )( 
            IFem2dPointLoad * This,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *GetForce )( 
            IFem2dPointLoad * This,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            IFem2dPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loading )( 
            IFem2dPointLoad * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        END_INTERFACE
    } IFem2dPointLoadVtbl;

    interface IFem2dPointLoad
    {
        CONST_VTBL struct IFem2dPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dPointLoad_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dPointLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IFem2dPointLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IFem2dPointLoad_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IFem2dPointLoad_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define IFem2dPointLoad_get_Fx(This,pVal)	\
    ( (This)->lpVtbl -> get_Fx(This,pVal) ) 

#define IFem2dPointLoad_put_Fx(This,newVal)	\
    ( (This)->lpVtbl -> put_Fx(This,newVal) ) 

#define IFem2dPointLoad_get_Fy(This,pVal)	\
    ( (This)->lpVtbl -> get_Fy(This,pVal) ) 

#define IFem2dPointLoad_put_Fy(This,newVal)	\
    ( (This)->lpVtbl -> put_Fy(This,newVal) ) 

#define IFem2dPointLoad_get_Mz(This,pVal)	\
    ( (This)->lpVtbl -> get_Mz(This,pVal) ) 

#define IFem2dPointLoad_put_Mz(This,newVal)	\
    ( (This)->lpVtbl -> put_Mz(This,newVal) ) 

#define IFem2dPointLoad_SetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> SetForce(This,Fx,Fy,Mz) ) 

#define IFem2dPointLoad_GetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> GetForce(This,Fx,Fy,Mz) ) 

#define IFem2dPointLoad_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IFem2dPointLoad_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#define IFem2dPointLoad_get_Loading(This,pVal)	\
    ( (This)->lpVtbl -> get_Loading(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dPointLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumPointLoad_INTERFACE_DEFINED__
#define __IFem2dEnumPointLoad_INTERFACE_DEFINED__

/* interface IFem2dEnumPointLoad */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED394556-BB29-11d4-AF47-00105A9AF985")
    IFem2dEnumPointLoad : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumPointLoad **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dPointLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumPointLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumPointLoad * This,
            /* [out] */ IFem2dEnumPointLoad **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumPointLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dPointLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumPointLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumPointLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumPointLoadVtbl;

    interface IFem2dEnumPointLoad
    {
        CONST_VTBL struct IFem2dEnumPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumPointLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumPointLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumPointLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumPointLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumPointLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dPointLoadCollection_INTERFACE_DEFINED__
#define __IFem2dPointLoadCollection_INTERFACE_DEFINED__

/* interface IFem2dPointLoadCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dPointLoadCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA256DDB-BB27-11d4-AF47-00105A9AF985")
    IFem2dPointLoadCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dPointLoad **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumPointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dPointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Float64 location,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [retval][out] */ IFem2dPointLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dPointLoadCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dPointLoadCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dPointLoadCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dPointLoadCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dPointLoadCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dPointLoad **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dPointLoadCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dPointLoadCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dPointLoadCollection * This,
            /* [retval][out] */ IFem2dEnumPointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dPointLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dPointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dPointLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Float64 location,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [retval][out] */ IFem2dPointLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dPointLoadCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dPointLoadCollection * This);
        
        END_INTERFACE
    } IFem2dPointLoadCollectionVtbl;

    interface IFem2dPointLoadCollection
    {
        CONST_VTBL struct IFem2dPointLoadCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dPointLoadCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dPointLoadCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dPointLoadCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dPointLoadCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dPointLoadCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dPointLoadCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dPointLoadCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dPointLoadCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dPointLoadCollection_Create(This,ID,memberID,location,Fx,Fy,Mz,orientation,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,memberID,location,Fx,Fy,Mz,orientation,pVal) ) 

#define IFem2dPointLoadCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dPointLoadCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dPointLoadCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dDistributedLoad_INTERFACE_DEFINED__
#define __IFem2dDistributedLoad_INTERFACE_DEFINED__

/* interface IFem2dDistributedLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B8719C2-D774-11d4-AF64-00105A9AF985")
    IFem2dDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ Fem2dLoadOrientation *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ Fem2dLoadOrientation newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ Fem2dLoadDirection *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ Fem2dLoadDirection newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StartLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_StartLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EndLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_EndLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_WStart( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_WStart( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_WEnd( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_WEnd( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loading( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dDistributedLoad * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IFem2dDistributedLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Fem2dLoadOrientation *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Fem2dLoadOrientation newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Fem2dLoadDirection *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Fem2dLoadDirection newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartLocation )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartLocation )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndLocation )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndLocation )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WStart )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WStart )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WEnd )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WEnd )( 
            IFem2dDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loading )( 
            IFem2dDistributedLoad * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        END_INTERFACE
    } IFem2dDistributedLoadVtbl;

    interface IFem2dDistributedLoad
    {
        CONST_VTBL struct IFem2dDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dDistributedLoad_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dDistributedLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IFem2dDistributedLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IFem2dDistributedLoad_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IFem2dDistributedLoad_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define IFem2dDistributedLoad_get_Direction(This,pVal)	\
    ( (This)->lpVtbl -> get_Direction(This,pVal) ) 

#define IFem2dDistributedLoad_put_Direction(This,newVal)	\
    ( (This)->lpVtbl -> put_Direction(This,newVal) ) 

#define IFem2dDistributedLoad_get_StartLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartLocation(This,pVal) ) 

#define IFem2dDistributedLoad_put_StartLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartLocation(This,newVal) ) 

#define IFem2dDistributedLoad_get_EndLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndLocation(This,pVal) ) 

#define IFem2dDistributedLoad_put_EndLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndLocation(This,newVal) ) 

#define IFem2dDistributedLoad_get_WStart(This,pVal)	\
    ( (This)->lpVtbl -> get_WStart(This,pVal) ) 

#define IFem2dDistributedLoad_put_WStart(This,newVal)	\
    ( (This)->lpVtbl -> put_WStart(This,newVal) ) 

#define IFem2dDistributedLoad_get_WEnd(This,pVal)	\
    ( (This)->lpVtbl -> get_WEnd(This,pVal) ) 

#define IFem2dDistributedLoad_put_WEnd(This,newVal)	\
    ( (This)->lpVtbl -> put_WEnd(This,newVal) ) 

#define IFem2dDistributedLoad_get_Loading(This,pVal)	\
    ( (This)->lpVtbl -> get_Loading(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumDistributedLoad_INTERFACE_DEFINED__
#define __IFem2dEnumDistributedLoad_INTERFACE_DEFINED__

/* interface IFem2dEnumDistributedLoad */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B8719C3-D774-11d4-AF64-00105A9AF985")
    IFem2dEnumDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumDistributedLoad **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dDistributedLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumDistributedLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumDistributedLoad * This,
            /* [out] */ IFem2dEnumDistributedLoad **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumDistributedLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dDistributedLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumDistributedLoad * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumDistributedLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumDistributedLoadVtbl;

    interface IFem2dEnumDistributedLoad
    {
        CONST_VTBL struct IFem2dEnumDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumDistributedLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumDistributedLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumDistributedLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumDistributedLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __IFem2dDistributedLoadCollection_INTERFACE_DEFINED__
#define __IFem2dDistributedLoadCollection_INTERFACE_DEFINED__

/* interface IFem2dDistributedLoadCollection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dDistributedLoadCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B8719C4-D774-11d4-AF64-00105A9AF985")
    IFem2dDistributedLoadCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dDistributedLoad **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumDistributedLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dDistributedLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dLoadDirection direction,
            /* [in] */ Float64 startLocation,
            /* [in] */ Float64 endLocation,
            /* [in] */ Float64 Wstart,
            /* [in] */ Float64 Wend,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [retval][out] */ IFem2dDistributedLoad **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dDistributedLoadCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dDistributedLoadCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dDistributedLoadCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dDistributedLoadCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dDistributedLoadCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dDistributedLoad **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dDistributedLoadCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dDistributedLoadCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dDistributedLoadCollection * This,
            /* [retval][out] */ IFem2dEnumDistributedLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dDistributedLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dDistributedLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dDistributedLoadCollection * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dLoadDirection direction,
            /* [in] */ Float64 startLocation,
            /* [in] */ Float64 endLocation,
            /* [in] */ Float64 Wstart,
            /* [in] */ Float64 Wend,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [retval][out] */ IFem2dDistributedLoad **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dDistributedLoadCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dDistributedLoadCollection * This);
        
        END_INTERFACE
    } IFem2dDistributedLoadCollectionVtbl;

    interface IFem2dDistributedLoadCollection
    {
        CONST_VTBL struct IFem2dDistributedLoadCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dDistributedLoadCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dDistributedLoadCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dDistributedLoadCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dDistributedLoadCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dDistributedLoadCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dDistributedLoadCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dDistributedLoadCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dDistributedLoadCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dDistributedLoadCollection_Create(This,ID,memberID,direction,startLocation,endLocation,Wstart,Wend,orientation,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,memberID,direction,startLocation,endLocation,Wstart,Wend,orientation,pVal) ) 

#define IFem2dDistributedLoadCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dDistributedLoadCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dDistributedLoadCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dMemberStrain_INTERFACE_DEFINED__
#define __IFem2dMemberStrain_INTERFACE_DEFINED__

/* interface IFem2dMemberStrain */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dMemberStrain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E07E9384-D113-11d4-AF5F-00105A9AF985")
    IFem2dMemberStrain : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AxialStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_AxialStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_CurvatureStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_CurvatureStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loading( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StartLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_StartLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_EndLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_EndLocation( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dMemberStrainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dMemberStrain * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dMemberStrain * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dMemberStrain * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ LoadIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IFem2dMemberStrain * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialStrain )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialStrain )( 
            IFem2dMemberStrain * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurvatureStrain )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurvatureStrain )( 
            IFem2dMemberStrain * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loading )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartLocation )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartLocation )( 
            IFem2dMemberStrain * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndLocation )( 
            IFem2dMemberStrain * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndLocation )( 
            IFem2dMemberStrain * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IFem2dMemberStrainVtbl;

    interface IFem2dMemberStrain
    {
        CONST_VTBL struct IFem2dMemberStrainVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dMemberStrain_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dMemberStrain_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dMemberStrain_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dMemberStrain_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dMemberStrain_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IFem2dMemberStrain_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IFem2dMemberStrain_get_AxialStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_AxialStrain(This,pVal) ) 

#define IFem2dMemberStrain_put_AxialStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_AxialStrain(This,newVal) ) 

#define IFem2dMemberStrain_get_CurvatureStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_CurvatureStrain(This,pVal) ) 

#define IFem2dMemberStrain_put_CurvatureStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_CurvatureStrain(This,newVal) ) 

#define IFem2dMemberStrain_get_Loading(This,pVal)	\
    ( (This)->lpVtbl -> get_Loading(This,pVal) ) 

#define IFem2dMemberStrain_get_StartLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartLocation(This,pVal) ) 

#define IFem2dMemberStrain_put_StartLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartLocation(This,newVal) ) 

#define IFem2dMemberStrain_get_EndLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndLocation(This,pVal) ) 

#define IFem2dMemberStrain_put_EndLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndLocation(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dMemberStrain_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumMemberStrain_INTERFACE_DEFINED__
#define __IFem2dEnumMemberStrain_INTERFACE_DEFINED__

/* interface IFem2dEnumMemberStrain */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumMemberStrain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E07E9385-D113-11d4-AF5F-00105A9AF985")
    IFem2dEnumMemberStrain : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumMemberStrain **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dMemberStrain **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumMemberStrainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumMemberStrain * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumMemberStrain * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumMemberStrain * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumMemberStrain * This,
            /* [out] */ IFem2dEnumMemberStrain **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumMemberStrain * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dMemberStrain **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumMemberStrain * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumMemberStrain * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumMemberStrainVtbl;

    interface IFem2dEnumMemberStrain
    {
        CONST_VTBL struct IFem2dEnumMemberStrainVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumMemberStrain_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumMemberStrain_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumMemberStrain_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumMemberStrain_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumMemberStrain_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumMemberStrain_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumMemberStrain_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumMemberStrain_INTERFACE_DEFINED__ */


#ifndef __IFem2dMemberStrainCollection_INTERFACE_DEFINED__
#define __IFem2dMemberStrainCollection_INTERFACE_DEFINED__

/* interface IFem2dMemberStrainCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dMemberStrainCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E07E9386-D113-11d4-AF5F-00105A9AF985")
    IFem2dMemberStrainCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dMemberStrain **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumMemberStrain **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dMemberStrain **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType member,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [in] */ Float64 axialStrain,
            /* [in] */ Float64 curvatureStrain,
            /* [retval][out] */ IFem2dMemberStrain **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dMemberStrainCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dMemberStrainCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dMemberStrainCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dMemberStrainCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dMemberStrainCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dMemberStrain **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dMemberStrainCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dMemberStrainCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dMemberStrainCollection * This,
            /* [retval][out] */ IFem2dEnumMemberStrain **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dMemberStrainCollection * This,
            /* [in] */ LoadIDType ID,
            /* [retval][out] */ IFem2dMemberStrain **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dMemberStrainCollection * This,
            /* [in] */ LoadIDType ID,
            /* [in] */ MemberIDType member,
            /* [in] */ Float64 start,
            /* [in] */ Float64 end,
            /* [in] */ Float64 axialStrain,
            /* [in] */ Float64 curvatureStrain,
            /* [retval][out] */ IFem2dMemberStrain **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dMemberStrainCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dMemberStrainCollection * This);
        
        END_INTERFACE
    } IFem2dMemberStrainCollectionVtbl;

    interface IFem2dMemberStrainCollection
    {
        CONST_VTBL struct IFem2dMemberStrainCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dMemberStrainCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dMemberStrainCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dMemberStrainCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dMemberStrainCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dMemberStrainCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dMemberStrainCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dMemberStrainCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dMemberStrainCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dMemberStrainCollection_Create(This,ID,member,start,end,axialStrain,curvatureStrain,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,member,start,end,axialStrain,curvatureStrain,pVal) ) 

#define IFem2dMemberStrainCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dMemberStrainCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dMemberStrainCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dLoading_INTERFACE_DEFINED__
#define __IFem2dLoading_INTERFACE_DEFINED__

/* interface IFem2dLoading */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dLoading;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("820F7F2A-BA41-11D4-AF46-00105A9AF985")
    IFem2dLoading : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ LoadCaseIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_JointLoads( 
            /* [retval][out] */ IFem2dJointLoadCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_DistributedLoads( 
            /* [retval][out] */ IFem2dDistributedLoadCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_JointDeflections( 
            /* [retval][out] */ IFem2dJointDeflectionCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PointLoads( 
            /* [retval][out] */ IFem2dPointLoadCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MemberStrains( 
            /* [retval][out] */ IFem2dMemberStrainCollection **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dLoadingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dLoading * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dLoading * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dLoading * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dLoading * This,
            /* [retval][out] */ LoadCaseIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JointLoads )( 
            IFem2dLoading * This,
            /* [retval][out] */ IFem2dJointLoadCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DistributedLoads )( 
            IFem2dLoading * This,
            /* [retval][out] */ IFem2dDistributedLoadCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_JointDeflections )( 
            IFem2dLoading * This,
            /* [retval][out] */ IFem2dJointDeflectionCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PointLoads )( 
            IFem2dLoading * This,
            /* [retval][out] */ IFem2dPointLoadCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberStrains )( 
            IFem2dLoading * This,
            /* [retval][out] */ IFem2dMemberStrainCollection **pVal);
        
        END_INTERFACE
    } IFem2dLoadingVtbl;

    interface IFem2dLoading
    {
        CONST_VTBL struct IFem2dLoadingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dLoading_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dLoading_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dLoading_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dLoading_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dLoading_get_JointLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_JointLoads(This,pVal) ) 

#define IFem2dLoading_get_DistributedLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_DistributedLoads(This,pVal) ) 

#define IFem2dLoading_get_JointDeflections(This,pVal)	\
    ( (This)->lpVtbl -> get_JointDeflections(This,pVal) ) 

#define IFem2dLoading_get_PointLoads(This,pVal)	\
    ( (This)->lpVtbl -> get_PointLoads(This,pVal) ) 

#define IFem2dLoading_get_MemberStrains(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberStrains(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dLoading_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumLoading_INTERFACE_DEFINED__
#define __IFem2dEnumLoading_INTERFACE_DEFINED__

/* interface IFem2dEnumLoading */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumLoading;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B3C129C-BA8E-11d4-AF46-00105A9AF985")
    IFem2dEnumLoading : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumLoading **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dLoading **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumLoadingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumLoading * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumLoading * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumLoading * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumLoading * This,
            /* [out] */ IFem2dEnumLoading **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumLoading * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dLoading **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumLoading * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumLoading * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumLoadingVtbl;

    interface IFem2dEnumLoading
    {
        CONST_VTBL struct IFem2dEnumLoadingVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumLoading_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumLoading_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumLoading_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumLoading_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumLoading_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumLoading_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumLoading_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumLoading_INTERFACE_DEFINED__ */


#ifndef __IFem2dLoadingCollection_INTERFACE_DEFINED__
#define __IFem2dLoadingCollection_INTERFACE_DEFINED__

/* interface IFem2dLoadingCollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dLoadingCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4B3C129D-BA8E-11d4-AF46-00105A9AF985")
    IFem2dLoadingCollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dLoading **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumLoading **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ LoadCaseIDType ID,
            /* [retval][out] */ IFem2dLoading **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ LoadCaseIDType ID,
            /* [retval][out] */ IFem2dLoading **ppLoading) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadCaseIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE RemoveIDLessThan( 
            /* [in] */ LoadCaseIDType id) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dLoadingCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dLoadingCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dLoadingCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dLoadingCollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dLoadingCollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dLoading **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dLoadingCollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dLoadingCollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dLoadingCollection * This,
            /* [retval][out] */ IFem2dEnumLoading **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dLoadingCollection * This,
            /* [in] */ LoadCaseIDType ID,
            /* [retval][out] */ IFem2dLoading **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dLoadingCollection * This,
            /* [in] */ LoadCaseIDType ID,
            /* [retval][out] */ IFem2dLoading **ppLoading);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dLoadingCollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ LoadCaseIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *RemoveIDLessThan )( 
            IFem2dLoadingCollection * This,
            /* [in] */ LoadCaseIDType id);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dLoadingCollection * This);
        
        END_INTERFACE
    } IFem2dLoadingCollectionVtbl;

    interface IFem2dLoadingCollection
    {
        CONST_VTBL struct IFem2dLoadingCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dLoadingCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dLoadingCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dLoadingCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dLoadingCollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dLoadingCollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dLoadingCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dLoadingCollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dLoadingCollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dLoadingCollection_Create(This,ID,ppLoading)	\
    ( (This)->lpVtbl -> Create(This,ID,ppLoading) ) 

#define IFem2dLoadingCollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dLoadingCollection_RemoveIDLessThan(This,id)	\
    ( (This)->lpVtbl -> RemoveIDLessThan(This,id) ) 

#define IFem2dLoadingCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dLoadingCollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dPOI_INTERFACE_DEFINED__
#define __IFem2dPOI_INTERFACE_DEFINED__

/* interface IFem2dPOI */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dPOI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC8FA5C3-C08D-11D4-AF4C-00105A9AF985")
    IFem2dPOI : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ PoiIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dPOIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dPOI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dPOI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dPOI * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            IFem2dPOI * This,
            /* [retval][out] */ PoiIDType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            IFem2dPOI * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            IFem2dPOI * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            IFem2dPOI * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            IFem2dPOI * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IFem2dPOIVtbl;

    interface IFem2dPOI
    {
        CONST_VTBL struct IFem2dPOIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dPOI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dPOI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dPOI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dPOI_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define IFem2dPOI_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define IFem2dPOI_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define IFem2dPOI_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define IFem2dPOI_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dPOI_INTERFACE_DEFINED__ */


#ifndef __IFem2dEnumPOI_INTERFACE_DEFINED__
#define __IFem2dEnumPOI_INTERFACE_DEFINED__

/* interface IFem2dEnumPOI */
/* [unique][restricted][hidden][oleautomation][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IFem2dEnumPOI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93740F38-C09C-11d4-AF4C-00105A9AF985")
    IFem2dEnumPOI : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IFem2dEnumPOI **ppenum) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dPOI **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dEnumPOIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dEnumPOI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dEnumPOI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dEnumPOI * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IFem2dEnumPOI * This,
            /* [out] */ IFem2dEnumPOI **ppenum);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IFem2dEnumPOI * This,
            /* [in] */ ULONG celt,
            /* [out] */ IFem2dPOI **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IFem2dEnumPOI * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IFem2dEnumPOI * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IFem2dEnumPOIVtbl;

    interface IFem2dEnumPOI
    {
        CONST_VTBL struct IFem2dEnumPOIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dEnumPOI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dEnumPOI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dEnumPOI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dEnumPOI_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define IFem2dEnumPOI_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IFem2dEnumPOI_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IFem2dEnumPOI_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dEnumPOI_INTERFACE_DEFINED__ */


#ifndef __IFem2dPOICollection_INTERFACE_DEFINED__
#define __IFem2dPOICollection_INTERFACE_DEFINED__

/* interface IFem2dPOICollection */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dPOICollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93740F39-C09C-11d4-AF4C-00105A9AF985")
    IFem2dPOICollection : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dPOI **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ IFem2dEnumPOI **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ PoiIDType ID,
            /* [retval][out] */ IFem2dPOI **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ PoiIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Float64 location,
            /* [retval][out] */ IFem2dPOI **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ PoiIDType *pid) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dPOICollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dPOICollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dPOICollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dPOICollection * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IFem2dPOICollection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ IFem2dPOI **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IFem2dPOICollection * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IFem2dPOICollection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            IFem2dPOICollection * This,
            /* [retval][out] */ IFem2dEnumPOI **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            IFem2dPOICollection * This,
            /* [in] */ PoiIDType ID,
            /* [retval][out] */ IFem2dPOI **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Create )( 
            IFem2dPOICollection * This,
            /* [in] */ PoiIDType ID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Float64 location,
            /* [retval][out] */ IFem2dPOI **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IFem2dPOICollection * This,
            /* [in] */ CollectionIndexType IDorIndex,
            /* [in] */ Fem2dAccessType AccessMethod,
            /* [retval][out] */ PoiIDType *pid);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dPOICollection * This);
        
        END_INTERFACE
    } IFem2dPOICollectionVtbl;

    interface IFem2dPOICollection
    {
        CONST_VTBL struct IFem2dPOICollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dPOICollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dPOICollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dPOICollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dPOICollection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define IFem2dPOICollection_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IFem2dPOICollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IFem2dPOICollection_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define IFem2dPOICollection_Find(This,ID,pVal)	\
    ( (This)->lpVtbl -> Find(This,ID,pVal) ) 

#define IFem2dPOICollection_Create(This,ID,memberID,location,pVal)	\
    ( (This)->lpVtbl -> Create(This,ID,memberID,location,pVal) ) 

#define IFem2dPOICollection_Remove(This,IDorIndex,AccessMethod,pid)	\
    ( (This)->lpVtbl -> Remove(This,IDorIndex,AccessMethod,pid) ) 

#define IFem2dPOICollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dPOICollection_INTERFACE_DEFINED__ */


#ifndef __IFem2dModelResults_INTERFACE_DEFINED__
#define __IFem2dModelResults_INTERFACE_DEFINED__

/* interface IFem2dModelResults */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dModelResults;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("10E2C871-FD3C-11d4-AF98-00105A9AF985")
    IFem2dModelResults : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeJointDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeMemberDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [out] */ Float64 *startDx,
            /* [out] */ Float64 *startDy,
            /* [out] */ Float64 *startRz,
            /* [out] */ Float64 *endDx,
            /* [out] */ Float64 *endDy,
            /* [out] */ Float64 *endRz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputePOIDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeMemberForces( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [out] */ Float64 *startFx,
            /* [out] */ Float64 *startFy,
            /* [out] */ Float64 *startMz,
            /* [out] */ Float64 *endFx,
            /* [out] */ Float64 *endFy,
            /* [out] */ Float64 *endMz) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputePOIForces( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dMbrFaceType face,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dModelResultsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dModelResults * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dModelResults * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dModelResults * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeJointDeflections )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeMemberDeflections )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [out] */ Float64 *startDx,
            /* [out] */ Float64 *startDy,
            /* [out] */ Float64 *startRz,
            /* [out] */ Float64 *endDx,
            /* [out] */ Float64 *endDy,
            /* [out] */ Float64 *endRz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputePOIDeflections )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *Dx,
            /* [out] */ Float64 *Dy,
            /* [out] */ Float64 *Rz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeMemberForces )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [out] */ Float64 *startFx,
            /* [out] */ Float64 *startFy,
            /* [out] */ Float64 *startMz,
            /* [out] */ Float64 *endFx,
            /* [out] */ Float64 *endFy,
            /* [out] */ Float64 *endMz);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputePOIForces )( 
            IFem2dModelResults * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dMbrFaceType face,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        END_INTERFACE
    } IFem2dModelResultsVtbl;

    interface IFem2dModelResults
    {
        CONST_VTBL struct IFem2dModelResultsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dModelResults_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dModelResults_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dModelResults_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dModelResults_ComputeJointDeflections(This,loadingID,jointID,Dx,Dy,Rz)	\
    ( (This)->lpVtbl -> ComputeJointDeflections(This,loadingID,jointID,Dx,Dy,Rz) ) 

#define IFem2dModelResults_ComputeMemberDeflections(This,loadingID,memberID,startDx,startDy,startRz,endDx,endDy,endRz)	\
    ( (This)->lpVtbl -> ComputeMemberDeflections(This,loadingID,memberID,startDx,startDy,startRz,endDx,endDy,endRz) ) 

#define IFem2dModelResults_ComputePOIDeflections(This,loadingID,poiID,orientation,Dx,Dy,Rz)	\
    ( (This)->lpVtbl -> ComputePOIDeflections(This,loadingID,poiID,orientation,Dx,Dy,Rz) ) 

#define IFem2dModelResults_ComputeReactions(This,loadingID,jointID,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> ComputeReactions(This,loadingID,jointID,Fx,Fy,Mz) ) 

#define IFem2dModelResults_ComputeMemberForces(This,loadingID,memberID,startFx,startFy,startMz,endFx,endFy,endMz)	\
    ( (This)->lpVtbl -> ComputeMemberForces(This,loadingID,memberID,startFx,startFy,startMz,endFx,endFy,endMz) ) 

#define IFem2dModelResults_ComputePOIForces(This,loadingID,poiID,face,orientation,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> ComputePOIForces(This,loadingID,poiID,face,orientation,Fx,Fy,Mz) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dModelResults_INTERFACE_DEFINED__ */


#ifndef __IFem2dModelResultsEx_INTERFACE_DEFINED__
#define __IFem2dModelResultsEx_INTERFACE_DEFINED__

/* interface IFem2dModelResultsEx */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dModelResultsEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("70470A1E-8806-4294-AFE9-57E402CB262C")
    IFem2dModelResultsEx : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeMemberForcesEx( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *startFx,
            /* [out] */ Float64 *startFy,
            /* [out] */ Float64 *startMz,
            /* [out] */ Float64 *endFx,
            /* [out] */ Float64 *endFy,
            /* [out] */ Float64 *endMz) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dModelResultsExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dModelResultsEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dModelResultsEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dModelResultsEx * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeMemberForcesEx )( 
            IFem2dModelResultsEx * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [out] */ Float64 *startFx,
            /* [out] */ Float64 *startFy,
            /* [out] */ Float64 *startMz,
            /* [out] */ Float64 *endFx,
            /* [out] */ Float64 *endFy,
            /* [out] */ Float64 *endMz);
        
        END_INTERFACE
    } IFem2dModelResultsExVtbl;

    interface IFem2dModelResultsEx
    {
        CONST_VTBL struct IFem2dModelResultsExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dModelResultsEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dModelResultsEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dModelResultsEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dModelResultsEx_ComputeMemberForcesEx(This,loadingID,memberID,orientation,startFx,startFy,startMz,endFx,endFy,endMz)	\
    ( (This)->lpVtbl -> ComputeMemberForcesEx(This,loadingID,memberID,orientation,startFx,startFy,startMz,endFx,endFy,endMz) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dModelResultsEx_INTERFACE_DEFINED__ */


#ifndef __IFem2dModelResultsForScriptingClients_INTERFACE_DEFINED__
#define __IFem2dModelResultsForScriptingClients_INTERFACE_DEFINED__

/* interface IFem2dModelResultsForScriptingClients */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dModelResultsForScriptingClients;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1861FF4B-FD4F-11d4-AF98-00105A9AF985")
    IFem2dModelResultsForScriptingClients : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeJointDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeMemberDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dMbrDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputePOIDeflections( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeReactions( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputeMemberForces( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dMbrDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ComputePOIForces( 
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dMbrFaceType face,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dModelResultsForScriptingClientsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dModelResultsForScriptingClients * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dModelResultsForScriptingClients * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeJointDeflections )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeMemberDeflections )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dMbrDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputePOIDeflections )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeReactions )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ JointIDType jointID,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputeMemberForces )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ MemberIDType memberID,
            /* [in] */ Fem2dMbrDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ComputePOIForces )( 
            IFem2dModelResultsForScriptingClients * This,
            /* [in] */ LoadCaseIDType loadingID,
            /* [in] */ PoiIDType poiID,
            /* [in] */ Fem2dMbrFaceType face,
            /* [in] */ Fem2dLoadOrientation orientation,
            /* [in] */ Fem2dJointDOF dof,
            /* [retval][out] */ Float64 *pVal);
        
        END_INTERFACE
    } IFem2dModelResultsForScriptingClientsVtbl;

    interface IFem2dModelResultsForScriptingClients
    {
        CONST_VTBL struct IFem2dModelResultsForScriptingClientsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dModelResultsForScriptingClients_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dModelResultsForScriptingClients_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dModelResultsForScriptingClients_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dModelResultsForScriptingClients_ComputeJointDeflections(This,loadingID,jointID,dof,pVal)	\
    ( (This)->lpVtbl -> ComputeJointDeflections(This,loadingID,jointID,dof,pVal) ) 

#define IFem2dModelResultsForScriptingClients_ComputeMemberDeflections(This,loadingID,memberID,dof,pVal)	\
    ( (This)->lpVtbl -> ComputeMemberDeflections(This,loadingID,memberID,dof,pVal) ) 

#define IFem2dModelResultsForScriptingClients_ComputePOIDeflections(This,loadingID,poiID,orientation,dof,pVal)	\
    ( (This)->lpVtbl -> ComputePOIDeflections(This,loadingID,poiID,orientation,dof,pVal) ) 

#define IFem2dModelResultsForScriptingClients_ComputeReactions(This,loadingID,jointID,dof,pVal)	\
    ( (This)->lpVtbl -> ComputeReactions(This,loadingID,jointID,dof,pVal) ) 

#define IFem2dModelResultsForScriptingClients_ComputeMemberForces(This,loadingID,memberID,dof,pVal)	\
    ( (This)->lpVtbl -> ComputeMemberForces(This,loadingID,memberID,dof,pVal) ) 

#define IFem2dModelResultsForScriptingClients_ComputePOIForces(This,loadingID,poiID,face,orientation,dof,pVal)	\
    ( (This)->lpVtbl -> ComputePOIForces(This,loadingID,poiID,face,orientation,dof,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dModelResultsForScriptingClients_INTERFACE_DEFINED__ */


#ifndef __IFem2dModel_INTERFACE_DEFINED__
#define __IFem2dModel_INTERFACE_DEFINED__

/* interface IFem2dModel */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IFem2dModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("807A6235-AE89-11D4-AF38-00105A9AF985")
    IFem2dModel : public IUnknown
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Joints( 
            /* [retval][out] */ IFem2dJointCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ IFem2dMemberCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Loadings( 
            /* [retval][out] */ IFem2dLoadingCollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_POIs( 
            /* [retval][out] */ IFem2dPOICollection **pVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Results( 
            /* [retval][out] */ IFem2dModelResultsForScriptingClients **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dModel * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dModel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dModel * This);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IFem2dModel * This,
            /* [in] */ BSTR name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IFem2dModel * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Joints )( 
            IFem2dModel * This,
            /* [retval][out] */ IFem2dJointCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Members )( 
            IFem2dModel * This,
            /* [retval][out] */ IFem2dMemberCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Loadings )( 
            IFem2dModel * This,
            /* [retval][out] */ IFem2dLoadingCollection **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_POIs )( 
            IFem2dModel * This,
            /* [retval][out] */ IFem2dPOICollection **pVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IFem2dModel * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Results )( 
            IFem2dModel * This,
            /* [retval][out] */ IFem2dModelResultsForScriptingClients **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IFem2dModel * This,
            /* [retval][out] */ IStructuredStorage2 **pVal);
        
        END_INTERFACE
    } IFem2dModelVtbl;

    interface IFem2dModel
    {
        CONST_VTBL struct IFem2dModelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dModel_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dModel_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dModel_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dModel_put_Name(This,name)	\
    ( (This)->lpVtbl -> put_Name(This,name) ) 

#define IFem2dModel_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IFem2dModel_get_Joints(This,pVal)	\
    ( (This)->lpVtbl -> get_Joints(This,pVal) ) 

#define IFem2dModel_get_Members(This,pVal)	\
    ( (This)->lpVtbl -> get_Members(This,pVal) ) 

#define IFem2dModel_get_Loadings(This,pVal)	\
    ( (This)->lpVtbl -> get_Loadings(This,pVal) ) 

#define IFem2dModel_get_POIs(This,pVal)	\
    ( (This)->lpVtbl -> get_POIs(This,pVal) ) 

#define IFem2dModel_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IFem2dModel_get_Results(This,pVal)	\
    ( (This)->lpVtbl -> get_Results(This,pVal) ) 

#define IFem2dModel_get_StructuredStorage(This,pVal)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dModel_INTERFACE_DEFINED__ */


#ifndef __IFem2dModelEvents_INTERFACE_DEFINED__
#define __IFem2dModelEvents_INTERFACE_DEFINED__

/* interface IFem2dModelEvents */
/* [object][unique][helpstring][oleautomation][helpcontext][uuid] */ 


EXTERN_C const IID IID_IFem2dModelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("807A6237-AE89-11D4-AF38-00105A9AF985")
    IFem2dModelEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnModelChanged( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnLoadingChanged( 
            /* [in] */ LoadCaseIDType loadingID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFem2dModelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFem2dModelEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFem2dModelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFem2dModelEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnModelChanged )( 
            IFem2dModelEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnLoadingChanged )( 
            IFem2dModelEvents * This,
            /* [in] */ LoadCaseIDType loadingID);
        
        END_INTERFACE
    } IFem2dModelEventsVtbl;

    interface IFem2dModelEvents
    {
        CONST_VTBL struct IFem2dModelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFem2dModelEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFem2dModelEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFem2dModelEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFem2dModelEvents_OnModelChanged(This)	\
    ( (This)->lpVtbl -> OnModelChanged(This) ) 

#define IFem2dModelEvents_OnLoadingChanged(This,loadingID)	\
    ( (This)->lpVtbl -> OnLoadingChanged(This,loadingID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFem2dModelEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Fem2dModel;

#ifdef __cplusplus

class DECLSPEC_UUID("807A6236-AE89-11D4-AF38-00105A9AF985")
Fem2dModel;
#endif

EXTERN_C const CLSID CLSID_Fem2dJointCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("807A6239-AE89-11D4-AF38-00105A9AF985")
Fem2dJointCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dJoint;

#ifdef __cplusplus

class DECLSPEC_UUID("5372D05A-9EBF-11D4-AF2B-00105A9AF985")
Fem2dJoint;
#endif

EXTERN_C const CLSID CLSID_Fem2dMember;

#ifdef __cplusplus

class DECLSPEC_UUID("3BA5C1A6-B009-11D4-AF39-00105A9AF985")
Fem2dMember;
#endif

EXTERN_C const CLSID CLSID_Fem2dMemberCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("F6ADC096-B057-11d4-AF39-00105A9AF985")
Fem2dMemberCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dJointLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("820F7F27-BA41-11D4-AF46-00105A9AF985")
Fem2dJointLoad;
#endif

EXTERN_C const CLSID CLSID_Fem2dJointLoadCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("820F7F29-BA41-11D4-AF46-00105A9AF985")
Fem2dJointLoadCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dJointDeflection;

#ifdef __cplusplus

class DECLSPEC_UUID("A5642479-CFBF-11d4-AF5D-00105A9AF985")
Fem2dJointDeflection;
#endif

EXTERN_C const CLSID CLSID_Fem2dJointDeflectionCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("A564247A-CFBF-11d4-AF5D-00105A9AF985")
Fem2dJointDeflectionCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dMemberStrain;

#ifdef __cplusplus

class DECLSPEC_UUID("E07E9387-D113-11d4-AF5F-00105A9AF985")
Fem2dMemberStrain;
#endif

EXTERN_C const CLSID CLSID_Fem2dMemberStrainCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("E07E9388-D113-11d4-AF5F-00105A9AF985")
Fem2dMemberStrainCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dLoading;

#ifdef __cplusplus

class DECLSPEC_UUID("820F7F2B-BA41-11D4-AF46-00105A9AF985")
Fem2dLoading;
#endif

EXTERN_C const CLSID CLSID_Fem2dLoadingCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("8DADA19F-BB07-11d4-AF47-00105A9AF985")
Fem2dLoadingCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dPointLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("50D65B04-BB0D-11D4-AF47-00105A9AF985")
Fem2dPointLoad;
#endif

EXTERN_C const CLSID CLSID_Fem2dPointLoadCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("6671D546-BB2A-11d4-AF47-00105A9AF985")
Fem2dPointLoadCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dDistributedLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("F7E1B926-D789-11d4-AF64-00105A9AF985")
Fem2dDistributedLoad;
#endif

EXTERN_C const CLSID CLSID_Fem2dDistributedLoadCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("F7E1B927-D789-11d4-AF64-00105A9AF985")
Fem2dDistributedLoadCollection;
#endif

EXTERN_C const CLSID CLSID_Fem2dPOI;

#ifdef __cplusplus

class DECLSPEC_UUID("FC8FA5C4-C08D-11D4-AF4C-00105A9AF985")
Fem2dPOI;
#endif

EXTERN_C const CLSID CLSID_Fem2dPOICollection;

#ifdef __cplusplus

class DECLSPEC_UUID("93740F3A-C09C-11d4-AF4C-00105A9AF985")
Fem2dPOICollection;
#endif
#endif /* __WBFLFem2d_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


