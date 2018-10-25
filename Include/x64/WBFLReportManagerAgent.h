

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:31:24 2017
 */
/* Compiler settings for ReportManagerAgent.idl:
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


#ifndef __WBFLReportManagerAgent_h__
#define __WBFLReportManagerAgent_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ReportManagerAgent_FWD_DEFINED__
#define __ReportManagerAgent_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReportManagerAgent ReportManagerAgent;
#else
typedef struct ReportManagerAgent ReportManagerAgent;
#endif /* __cplusplus */

#endif 	/* __ReportManagerAgent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLCore.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLReportManagerAgent_LIBRARY_DEFINED__
#define __WBFLReportManagerAgent_LIBRARY_DEFINED__

/* library WBFLReportManagerAgent */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLReportManagerAgent;

EXTERN_C const CLSID CLSID_ReportManagerAgent;

#ifdef __cplusplus

class DECLSPEC_UUID("809889B1-69F0-49FC-B8F5-50B0BC169EB0")
ReportManagerAgent;
#endif
#endif /* __WBFLReportManagerAgent_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


