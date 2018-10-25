

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:46:10 2017
 */
/* Compiler settings for ..\Include\WBFLDManipTools.idl:
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


#ifndef __WBFLDManipTools_h__
#define __WBFLDManipTools_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __PolyLineDisplayObject_FWD_DEFINED__
#define __PolyLineDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class PolyLineDisplayObject PolyLineDisplayObject;
#else
typedef struct PolyLineDisplayObject PolyLineDisplayObject;
#endif /* __cplusplus */

#endif 	/* __PolyLineDisplayObject_FWD_DEFINED__ */


#ifndef __HorzCurveDisplayObject_FWD_DEFINED__
#define __HorzCurveDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class HorzCurveDisplayObject HorzCurveDisplayObject;
#else
typedef struct HorzCurveDisplayObject HorzCurveDisplayObject;
#endif /* __cplusplus */

#endif 	/* __HorzCurveDisplayObject_FWD_DEFINED__ */


#ifndef __GraphXyDisplayObject_FWD_DEFINED__
#define __GraphXyDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class GraphXyDisplayObject GraphXyDisplayObject;
#else
typedef struct GraphXyDisplayObject GraphXyDisplayObject;
#endif /* __cplusplus */

#endif 	/* __GraphXyDisplayObject_FWD_DEFINED__ */


#ifndef __DataSet2d_FWD_DEFINED__
#define __DataSet2d_FWD_DEFINED__

#ifdef __cplusplus
typedef class DataSet2d DataSet2d;
#else
typedef struct DataSet2d DataSet2d;
#endif /* __cplusplus */

#endif 	/* __DataSet2d_FWD_DEFINED__ */


#ifndef __LegendDisplayObject_FWD_DEFINED__
#define __LegendDisplayObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class LegendDisplayObject LegendDisplayObject;
#else
typedef struct LegendDisplayObject LegendDisplayObject;
#endif /* __cplusplus */

#endif 	/* __LegendDisplayObject_FWD_DEFINED__ */


#ifndef __LegendEntry_FWD_DEFINED__
#define __LegendEntry_FWD_DEFINED__

#ifdef __cplusplus
typedef class LegendEntry LegendEntry;
#else
typedef struct LegendEntry LegendEntry;
#endif /* __cplusplus */

#endif 	/* __LegendEntry_FWD_DEFINED__ */


#ifndef __DManipToolsDisplayObjectFactory_FWD_DEFINED__
#define __DManipToolsDisplayObjectFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class DManipToolsDisplayObjectFactory DManipToolsDisplayObjectFactory;
#else
typedef struct DManipToolsDisplayObjectFactory DManipToolsDisplayObjectFactory;
#endif /* __cplusplus */

#endif 	/* __DManipToolsDisplayObjectFactory_FWD_DEFINED__ */


#ifndef __GraphXyDataProvider_FWD_DEFINED__
#define __GraphXyDataProvider_FWD_DEFINED__

#ifdef __cplusplus
typedef class GraphXyDataProvider GraphXyDataProvider;
#else
typedef struct GraphXyDataProvider GraphXyDataProvider;
#endif /* __cplusplus */

#endif 	/* __GraphXyDataProvider_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLDManipTools_LIBRARY_DEFINED__
#define __WBFLDManipTools_LIBRARY_DEFINED__

/* library WBFLDManipTools */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLDManipTools;

EXTERN_C const CLSID CLSID_PolyLineDisplayObject;

#ifdef __cplusplus

class DECLSPEC_UUID("341A682F-5B58-4f63-8190-88BF3970FB45")
PolyLineDisplayObject;
#endif

EXTERN_C const CLSID CLSID_HorzCurveDisplayObject;

#ifdef __cplusplus

class DECLSPEC_UUID("7DBA44AA-1542-4470-8719-21580A6822B5")
HorzCurveDisplayObject;
#endif

EXTERN_C const CLSID CLSID_GraphXyDisplayObject;

#ifdef __cplusplus

class DECLSPEC_UUID("06C90828-5269-4b98-97E6-AECDDF4B0764")
GraphXyDisplayObject;
#endif

EXTERN_C const CLSID CLSID_DataSet2d;

#ifdef __cplusplus

class DECLSPEC_UUID("4792CF33-B6FD-423F-90DE-314356A22848")
DataSet2d;
#endif

EXTERN_C const CLSID CLSID_LegendDisplayObject;

#ifdef __cplusplus

class DECLSPEC_UUID("C2EC59B5-BAA1-437d-89CB-19AD85ED9F04")
LegendDisplayObject;
#endif

EXTERN_C const CLSID CLSID_LegendEntry;

#ifdef __cplusplus

class DECLSPEC_UUID("951403BB-85F3-4443-8EE9-4FFDB338F3F5")
LegendEntry;
#endif

EXTERN_C const CLSID CLSID_DManipToolsDisplayObjectFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("D7C33DA2-EE8F-49a1-9A13-8653809262E9")
DManipToolsDisplayObjectFactory;
#endif

EXTERN_C const CLSID CLSID_GraphXyDataProvider;

#ifdef __cplusplus

class DECLSPEC_UUID("0462D6DF-25DB-4fa0-B8B2-7B855A702A99")
GraphXyDataProvider;
#endif
#endif /* __WBFLDManipTools_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


