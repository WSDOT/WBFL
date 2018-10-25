

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:33:03 2017
 */
/* Compiler settings for GraphManagerAgent.idl:
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


#ifndef __WBFLGraphManagerAgent_h__
#define __WBFLGraphManagerAgent_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __GraphManagerAgent_FWD_DEFINED__
#define __GraphManagerAgent_FWD_DEFINED__

#ifdef __cplusplus
typedef class GraphManagerAgent GraphManagerAgent;
#else
typedef struct GraphManagerAgent GraphManagerAgent;
#endif /* __cplusplus */

#endif 	/* __GraphManagerAgent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLCore.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLGraphManagerAgent_LIBRARY_DEFINED__
#define __WBFLGraphManagerAgent_LIBRARY_DEFINED__

/* library WBFLGraphManagerAgent */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLGraphManagerAgent;

EXTERN_C const CLSID CLSID_GraphManagerAgent;

#ifdef __cplusplus

class DECLSPEC_UUID("1611AC48-FDC6-4f3d-AE54-DB9F7615821D")
GraphManagerAgent;
#endif
#endif /* __WBFLGraphManagerAgent_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


