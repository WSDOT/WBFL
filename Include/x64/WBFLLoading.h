

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:27:01 2017
 */
/* Compiler settings for ..\Include\WBFLLoading.idl:
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


#ifndef __WBFLLoading_h__
#define __WBFLLoading_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ldIPointLoad_FWD_DEFINED__
#define __ldIPointLoad_FWD_DEFINED__
typedef interface ldIPointLoad ldIPointLoad;

#endif 	/* __ldIPointLoad_FWD_DEFINED__ */


#ifndef __ldIPointLoadEvents_FWD_DEFINED__
#define __ldIPointLoadEvents_FWD_DEFINED__
typedef interface ldIPointLoadEvents ldIPointLoadEvents;

#endif 	/* __ldIPointLoadEvents_FWD_DEFINED__ */


#ifndef __ldIPointLoadItem_FWD_DEFINED__
#define __ldIPointLoadItem_FWD_DEFINED__
typedef interface ldIPointLoadItem ldIPointLoadItem;

#endif 	/* __ldIPointLoadItem_FWD_DEFINED__ */


#ifndef __ldIEnumPointLoad_FWD_DEFINED__
#define __ldIEnumPointLoad_FWD_DEFINED__
typedef interface ldIEnumPointLoad ldIEnumPointLoad;

#endif 	/* __ldIEnumPointLoad_FWD_DEFINED__ */


#ifndef __ldIPointLoads_FWD_DEFINED__
#define __ldIPointLoads_FWD_DEFINED__
typedef interface ldIPointLoads ldIPointLoads;

#endif 	/* __ldIPointLoads_FWD_DEFINED__ */


#ifndef __ldIPointLoadsEvents_FWD_DEFINED__
#define __ldIPointLoadsEvents_FWD_DEFINED__
typedef interface ldIPointLoadsEvents ldIPointLoadsEvents;

#endif 	/* __ldIPointLoadsEvents_FWD_DEFINED__ */


#ifndef __ldIDistributedLoad_FWD_DEFINED__
#define __ldIDistributedLoad_FWD_DEFINED__
typedef interface ldIDistributedLoad ldIDistributedLoad;

#endif 	/* __ldIDistributedLoad_FWD_DEFINED__ */


#ifndef __ldIDistributedLoadEvents_FWD_DEFINED__
#define __ldIDistributedLoadEvents_FWD_DEFINED__
typedef interface ldIDistributedLoadEvents ldIDistributedLoadEvents;

#endif 	/* __ldIDistributedLoadEvents_FWD_DEFINED__ */


#ifndef __ldIDistributedLoadItem_FWD_DEFINED__
#define __ldIDistributedLoadItem_FWD_DEFINED__
typedef interface ldIDistributedLoadItem ldIDistributedLoadItem;

#endif 	/* __ldIDistributedLoadItem_FWD_DEFINED__ */


#ifndef __ldIEnumDistributedLoad_FWD_DEFINED__
#define __ldIEnumDistributedLoad_FWD_DEFINED__
typedef interface ldIEnumDistributedLoad ldIEnumDistributedLoad;

#endif 	/* __ldIEnumDistributedLoad_FWD_DEFINED__ */


#ifndef __ldIDistributedLoads_FWD_DEFINED__
#define __ldIDistributedLoads_FWD_DEFINED__
typedef interface ldIDistributedLoads ldIDistributedLoads;

#endif 	/* __ldIDistributedLoads_FWD_DEFINED__ */


#ifndef __ldIDistributedLoadsEvents_FWD_DEFINED__
#define __ldIDistributedLoadsEvents_FWD_DEFINED__
typedef interface ldIDistributedLoadsEvents ldIDistributedLoadsEvents;

#endif 	/* __ldIDistributedLoadsEvents_FWD_DEFINED__ */


#ifndef __ldISettlementLoad_FWD_DEFINED__
#define __ldISettlementLoad_FWD_DEFINED__
typedef interface ldISettlementLoad ldISettlementLoad;

#endif 	/* __ldISettlementLoad_FWD_DEFINED__ */


#ifndef __ldISettlementLoadEvents_FWD_DEFINED__
#define __ldISettlementLoadEvents_FWD_DEFINED__
typedef interface ldISettlementLoadEvents ldISettlementLoadEvents;

#endif 	/* __ldISettlementLoadEvents_FWD_DEFINED__ */


#ifndef __ldISettlementLoadItem_FWD_DEFINED__
#define __ldISettlementLoadItem_FWD_DEFINED__
typedef interface ldISettlementLoadItem ldISettlementLoadItem;

#endif 	/* __ldISettlementLoadItem_FWD_DEFINED__ */


#ifndef __ldIEnumSettlementLoad_FWD_DEFINED__
#define __ldIEnumSettlementLoad_FWD_DEFINED__
typedef interface ldIEnumSettlementLoad ldIEnumSettlementLoad;

#endif 	/* __ldIEnumSettlementLoad_FWD_DEFINED__ */


#ifndef __ldISettlementLoads_FWD_DEFINED__
#define __ldISettlementLoads_FWD_DEFINED__
typedef interface ldISettlementLoads ldISettlementLoads;

#endif 	/* __ldISettlementLoads_FWD_DEFINED__ */


#ifndef __ldISettlementLoadsEvents_FWD_DEFINED__
#define __ldISettlementLoadsEvents_FWD_DEFINED__
typedef interface ldISettlementLoadsEvents ldISettlementLoadsEvents;

#endif 	/* __ldISettlementLoadsEvents_FWD_DEFINED__ */


#ifndef __ldITemperatureLoad_FWD_DEFINED__
#define __ldITemperatureLoad_FWD_DEFINED__
typedef interface ldITemperatureLoad ldITemperatureLoad;

#endif 	/* __ldITemperatureLoad_FWD_DEFINED__ */


#ifndef __ldITemperatureLoadEvents_FWD_DEFINED__
#define __ldITemperatureLoadEvents_FWD_DEFINED__
typedef interface ldITemperatureLoadEvents ldITemperatureLoadEvents;

#endif 	/* __ldITemperatureLoadEvents_FWD_DEFINED__ */


#ifndef __ldITemperatureLoadItem_FWD_DEFINED__
#define __ldITemperatureLoadItem_FWD_DEFINED__
typedef interface ldITemperatureLoadItem ldITemperatureLoadItem;

#endif 	/* __ldITemperatureLoadItem_FWD_DEFINED__ */


#ifndef __ldIEnumTemperatureLoad_FWD_DEFINED__
#define __ldIEnumTemperatureLoad_FWD_DEFINED__
typedef interface ldIEnumTemperatureLoad ldIEnumTemperatureLoad;

#endif 	/* __ldIEnumTemperatureLoad_FWD_DEFINED__ */


#ifndef __ldITemperatureLoads_FWD_DEFINED__
#define __ldITemperatureLoads_FWD_DEFINED__
typedef interface ldITemperatureLoads ldITemperatureLoads;

#endif 	/* __ldITemperatureLoads_FWD_DEFINED__ */


#ifndef __ldITemperatureLoadsEvents_FWD_DEFINED__
#define __ldITemperatureLoadsEvents_FWD_DEFINED__
typedef interface ldITemperatureLoadsEvents ldITemperatureLoadsEvents;

#endif 	/* __ldITemperatureLoadsEvents_FWD_DEFINED__ */


#ifndef __ldIStrainLoad_FWD_DEFINED__
#define __ldIStrainLoad_FWD_DEFINED__
typedef interface ldIStrainLoad ldIStrainLoad;

#endif 	/* __ldIStrainLoad_FWD_DEFINED__ */


#ifndef __ldIStrainLoadEvents_FWD_DEFINED__
#define __ldIStrainLoadEvents_FWD_DEFINED__
typedef interface ldIStrainLoadEvents ldIStrainLoadEvents;

#endif 	/* __ldIStrainLoadEvents_FWD_DEFINED__ */


#ifndef __ldIStrainLoadItem_FWD_DEFINED__
#define __ldIStrainLoadItem_FWD_DEFINED__
typedef interface ldIStrainLoadItem ldIStrainLoadItem;

#endif 	/* __ldIStrainLoadItem_FWD_DEFINED__ */


#ifndef __ldIEnumStrainLoad_FWD_DEFINED__
#define __ldIEnumStrainLoad_FWD_DEFINED__
typedef interface ldIEnumStrainLoad ldIEnumStrainLoad;

#endif 	/* __ldIEnumStrainLoad_FWD_DEFINED__ */


#ifndef __ldIStrainLoads_FWD_DEFINED__
#define __ldIStrainLoads_FWD_DEFINED__
typedef interface ldIStrainLoads ldIStrainLoads;

#endif 	/* __ldIStrainLoads_FWD_DEFINED__ */


#ifndef __ldIStrainLoadsEvents_FWD_DEFINED__
#define __ldIStrainLoadsEvents_FWD_DEFINED__
typedef interface ldIStrainLoadsEvents ldIStrainLoadsEvents;

#endif 	/* __ldIStrainLoadsEvents_FWD_DEFINED__ */


#ifndef __ldIAxle_FWD_DEFINED__
#define __ldIAxle_FWD_DEFINED__
typedef interface ldIAxle ldIAxle;

#endif 	/* __ldIAxle_FWD_DEFINED__ */


#ifndef __ldIAxleEvents_FWD_DEFINED__
#define __ldIAxleEvents_FWD_DEFINED__
typedef interface ldIAxleEvents ldIAxleEvents;

#endif 	/* __ldIAxleEvents_FWD_DEFINED__ */


#ifndef __ldIEnumAxle_FWD_DEFINED__
#define __ldIEnumAxle_FWD_DEFINED__
typedef interface ldIEnumAxle ldIEnumAxle;

#endif 	/* __ldIEnumAxle_FWD_DEFINED__ */


#ifndef __ldIAxles_FWD_DEFINED__
#define __ldIAxles_FWD_DEFINED__
typedef interface ldIAxles ldIAxles;

#endif 	/* __ldIAxles_FWD_DEFINED__ */


#ifndef __ldIAxlesEvents_FWD_DEFINED__
#define __ldIAxlesEvents_FWD_DEFINED__
typedef interface ldIAxlesEvents ldIAxlesEvents;

#endif 	/* __ldIAxlesEvents_FWD_DEFINED__ */


#ifndef __ldIVehicularLoad_FWD_DEFINED__
#define __ldIVehicularLoad_FWD_DEFINED__
typedef interface ldIVehicularLoad ldIVehicularLoad;

#endif 	/* __ldIVehicularLoad_FWD_DEFINED__ */


#ifndef __ldIVehicularLoadEvents_FWD_DEFINED__
#define __ldIVehicularLoadEvents_FWD_DEFINED__
typedef interface ldIVehicularLoadEvents ldIVehicularLoadEvents;

#endif 	/* __ldIVehicularLoadEvents_FWD_DEFINED__ */


#ifndef __ldIEnumVehicularLoad_FWD_DEFINED__
#define __ldIEnumVehicularLoad_FWD_DEFINED__
typedef interface ldIEnumVehicularLoad ldIEnumVehicularLoad;

#endif 	/* __ldIEnumVehicularLoad_FWD_DEFINED__ */


#ifndef __ldIVehicularLoads_FWD_DEFINED__
#define __ldIVehicularLoads_FWD_DEFINED__
typedef interface ldIVehicularLoads ldIVehicularLoads;

#endif 	/* __ldIVehicularLoads_FWD_DEFINED__ */


#ifndef __ldIVehicularLoadsEvents_FWD_DEFINED__
#define __ldIVehicularLoadsEvents_FWD_DEFINED__
typedef interface ldIVehicularLoadsEvents ldIVehicularLoadsEvents;

#endif 	/* __ldIVehicularLoadsEvents_FWD_DEFINED__ */


#ifndef __ldILoadGroup_FWD_DEFINED__
#define __ldILoadGroup_FWD_DEFINED__
typedef interface ldILoadGroup ldILoadGroup;

#endif 	/* __ldILoadGroup_FWD_DEFINED__ */


#ifndef __ldILoadGroupEvents_FWD_DEFINED__
#define __ldILoadGroupEvents_FWD_DEFINED__
typedef interface ldILoadGroupEvents ldILoadGroupEvents;

#endif 	/* __ldILoadGroupEvents_FWD_DEFINED__ */


#ifndef __ldIEnumLoadGroup_FWD_DEFINED__
#define __ldIEnumLoadGroup_FWD_DEFINED__
typedef interface ldIEnumLoadGroup ldIEnumLoadGroup;

#endif 	/* __ldIEnumLoadGroup_FWD_DEFINED__ */


#ifndef __ldILoadGroups_FWD_DEFINED__
#define __ldILoadGroups_FWD_DEFINED__
typedef interface ldILoadGroups ldILoadGroups;

#endif 	/* __ldILoadGroups_FWD_DEFINED__ */


#ifndef __ldILoadGroupsEvents_FWD_DEFINED__
#define __ldILoadGroupsEvents_FWD_DEFINED__
typedef interface ldILoadGroupsEvents ldILoadGroupsEvents;

#endif 	/* __ldILoadGroupsEvents_FWD_DEFINED__ */


#ifndef __ldILoadCase_FWD_DEFINED__
#define __ldILoadCase_FWD_DEFINED__
typedef interface ldILoadCase ldILoadCase;

#endif 	/* __ldILoadCase_FWD_DEFINED__ */


#ifndef __ldILoadCaseEvents_FWD_DEFINED__
#define __ldILoadCaseEvents_FWD_DEFINED__
typedef interface ldILoadCaseEvents ldILoadCaseEvents;

#endif 	/* __ldILoadCaseEvents_FWD_DEFINED__ */


#ifndef __ldIEnumLoadCase_FWD_DEFINED__
#define __ldIEnumLoadCase_FWD_DEFINED__
typedef interface ldIEnumLoadCase ldIEnumLoadCase;

#endif 	/* __ldIEnumLoadCase_FWD_DEFINED__ */


#ifndef __ldILoadCases_FWD_DEFINED__
#define __ldILoadCases_FWD_DEFINED__
typedef interface ldILoadCases ldILoadCases;

#endif 	/* __ldILoadCases_FWD_DEFINED__ */


#ifndef __ldILoadCasesEvents_FWD_DEFINED__
#define __ldILoadCasesEvents_FWD_DEFINED__
typedef interface ldILoadCasesEvents ldILoadCasesEvents;

#endif 	/* __ldILoadCasesEvents_FWD_DEFINED__ */


#ifndef __ldILoadCombination_FWD_DEFINED__
#define __ldILoadCombination_FWD_DEFINED__
typedef interface ldILoadCombination ldILoadCombination;

#endif 	/* __ldILoadCombination_FWD_DEFINED__ */


#ifndef __ldILoadCombinationEvents_FWD_DEFINED__
#define __ldILoadCombinationEvents_FWD_DEFINED__
typedef interface ldILoadCombinationEvents ldILoadCombinationEvents;

#endif 	/* __ldILoadCombinationEvents_FWD_DEFINED__ */


#ifndef __ldIEnumLoadCombination_FWD_DEFINED__
#define __ldIEnumLoadCombination_FWD_DEFINED__
typedef interface ldIEnumLoadCombination ldIEnumLoadCombination;

#endif 	/* __ldIEnumLoadCombination_FWD_DEFINED__ */


#ifndef __ldILoadCombinations_FWD_DEFINED__
#define __ldILoadCombinations_FWD_DEFINED__
typedef interface ldILoadCombinations ldILoadCombinations;

#endif 	/* __ldILoadCombinations_FWD_DEFINED__ */


#ifndef __ldILoadCombinationsEvents_FWD_DEFINED__
#define __ldILoadCombinationsEvents_FWD_DEFINED__
typedef interface ldILoadCombinationsEvents ldILoadCombinationsEvents;

#endif 	/* __ldILoadCombinationsEvents_FWD_DEFINED__ */


#ifndef __ldPointLoad_FWD_DEFINED__
#define __ldPointLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldPointLoad ldPointLoad;
#else
typedef struct ldPointLoad ldPointLoad;
#endif /* __cplusplus */

#endif 	/* __ldPointLoad_FWD_DEFINED__ */


#ifndef __ldPointLoadItem_FWD_DEFINED__
#define __ldPointLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldPointLoadItem ldPointLoadItem;
#else
typedef struct ldPointLoadItem ldPointLoadItem;
#endif /* __cplusplus */

#endif 	/* __ldPointLoadItem_FWD_DEFINED__ */


#ifndef __ldPointLoads_FWD_DEFINED__
#define __ldPointLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldPointLoads ldPointLoads;
#else
typedef struct ldPointLoads ldPointLoads;
#endif /* __cplusplus */

#endif 	/* __ldPointLoads_FWD_DEFINED__ */


#ifndef __ldDistributedLoad_FWD_DEFINED__
#define __ldDistributedLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldDistributedLoad ldDistributedLoad;
#else
typedef struct ldDistributedLoad ldDistributedLoad;
#endif /* __cplusplus */

#endif 	/* __ldDistributedLoad_FWD_DEFINED__ */


#ifndef __ldDistributedLoadItem_FWD_DEFINED__
#define __ldDistributedLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldDistributedLoadItem ldDistributedLoadItem;
#else
typedef struct ldDistributedLoadItem ldDistributedLoadItem;
#endif /* __cplusplus */

#endif 	/* __ldDistributedLoadItem_FWD_DEFINED__ */


#ifndef __ldDistributedLoads_FWD_DEFINED__
#define __ldDistributedLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldDistributedLoads ldDistributedLoads;
#else
typedef struct ldDistributedLoads ldDistributedLoads;
#endif /* __cplusplus */

#endif 	/* __ldDistributedLoads_FWD_DEFINED__ */


#ifndef __ldSettlementLoad_FWD_DEFINED__
#define __ldSettlementLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldSettlementLoad ldSettlementLoad;
#else
typedef struct ldSettlementLoad ldSettlementLoad;
#endif /* __cplusplus */

#endif 	/* __ldSettlementLoad_FWD_DEFINED__ */


#ifndef __ldSettlementLoadItem_FWD_DEFINED__
#define __ldSettlementLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldSettlementLoadItem ldSettlementLoadItem;
#else
typedef struct ldSettlementLoadItem ldSettlementLoadItem;
#endif /* __cplusplus */

#endif 	/* __ldSettlementLoadItem_FWD_DEFINED__ */


#ifndef __ldSettlementLoads_FWD_DEFINED__
#define __ldSettlementLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldSettlementLoads ldSettlementLoads;
#else
typedef struct ldSettlementLoads ldSettlementLoads;
#endif /* __cplusplus */

#endif 	/* __ldSettlementLoads_FWD_DEFINED__ */


#ifndef __ldTemperatureLoad_FWD_DEFINED__
#define __ldTemperatureLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldTemperatureLoad ldTemperatureLoad;
#else
typedef struct ldTemperatureLoad ldTemperatureLoad;
#endif /* __cplusplus */

#endif 	/* __ldTemperatureLoad_FWD_DEFINED__ */


#ifndef __ldTemperatureLoadItem_FWD_DEFINED__
#define __ldTemperatureLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldTemperatureLoadItem ldTemperatureLoadItem;
#else
typedef struct ldTemperatureLoadItem ldTemperatureLoadItem;
#endif /* __cplusplus */

#endif 	/* __ldTemperatureLoadItem_FWD_DEFINED__ */


#ifndef __ldTemperatureLoads_FWD_DEFINED__
#define __ldTemperatureLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldTemperatureLoads ldTemperatureLoads;
#else
typedef struct ldTemperatureLoads ldTemperatureLoads;
#endif /* __cplusplus */

#endif 	/* __ldTemperatureLoads_FWD_DEFINED__ */


#ifndef __ldStrainLoad_FWD_DEFINED__
#define __ldStrainLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldStrainLoad ldStrainLoad;
#else
typedef struct ldStrainLoad ldStrainLoad;
#endif /* __cplusplus */

#endif 	/* __ldStrainLoad_FWD_DEFINED__ */


#ifndef __ldStrainLoadItem_FWD_DEFINED__
#define __ldStrainLoadItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldStrainLoadItem ldStrainLoadItem;
#else
typedef struct ldStrainLoadItem ldStrainLoadItem;
#endif /* __cplusplus */

#endif 	/* __ldStrainLoadItem_FWD_DEFINED__ */


#ifndef __ldStrainLoads_FWD_DEFINED__
#define __ldStrainLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldStrainLoads ldStrainLoads;
#else
typedef struct ldStrainLoads ldStrainLoads;
#endif /* __cplusplus */

#endif 	/* __ldStrainLoads_FWD_DEFINED__ */


#ifndef __ldAxle_FWD_DEFINED__
#define __ldAxle_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldAxle ldAxle;
#else
typedef struct ldAxle ldAxle;
#endif /* __cplusplus */

#endif 	/* __ldAxle_FWD_DEFINED__ */


#ifndef __ldAxles_FWD_DEFINED__
#define __ldAxles_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldAxles ldAxles;
#else
typedef struct ldAxles ldAxles;
#endif /* __cplusplus */

#endif 	/* __ldAxles_FWD_DEFINED__ */


#ifndef __ldVehicularLoad_FWD_DEFINED__
#define __ldVehicularLoad_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldVehicularLoad ldVehicularLoad;
#else
typedef struct ldVehicularLoad ldVehicularLoad;
#endif /* __cplusplus */

#endif 	/* __ldVehicularLoad_FWD_DEFINED__ */


#ifndef __ldVehicularLoads_FWD_DEFINED__
#define __ldVehicularLoads_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldVehicularLoads ldVehicularLoads;
#else
typedef struct ldVehicularLoads ldVehicularLoads;
#endif /* __cplusplus */

#endif 	/* __ldVehicularLoads_FWD_DEFINED__ */


#ifndef __ldLoadGroup_FWD_DEFINED__
#define __ldLoadGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadGroup ldLoadGroup;
#else
typedef struct ldLoadGroup ldLoadGroup;
#endif /* __cplusplus */

#endif 	/* __ldLoadGroup_FWD_DEFINED__ */


#ifndef __ldLoadGroups_FWD_DEFINED__
#define __ldLoadGroups_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadGroups ldLoadGroups;
#else
typedef struct ldLoadGroups ldLoadGroups;
#endif /* __cplusplus */

#endif 	/* __ldLoadGroups_FWD_DEFINED__ */


#ifndef __ldLoadCase_FWD_DEFINED__
#define __ldLoadCase_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadCase ldLoadCase;
#else
typedef struct ldLoadCase ldLoadCase;
#endif /* __cplusplus */

#endif 	/* __ldLoadCase_FWD_DEFINED__ */


#ifndef __ldLoadCases_FWD_DEFINED__
#define __ldLoadCases_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadCases ldLoadCases;
#else
typedef struct ldLoadCases ldLoadCases;
#endif /* __cplusplus */

#endif 	/* __ldLoadCases_FWD_DEFINED__ */


#ifndef __ldLoadCombination_FWD_DEFINED__
#define __ldLoadCombination_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadCombination ldLoadCombination;
#else
typedef struct ldLoadCombination ldLoadCombination;
#endif /* __cplusplus */

#endif 	/* __ldLoadCombination_FWD_DEFINED__ */


#ifndef __ldLoadCombinations_FWD_DEFINED__
#define __ldLoadCombinations_FWD_DEFINED__

#ifdef __cplusplus
typedef class ldLoadCombinations ldLoadCombinations;
#else
typedef struct ldLoadCombinations ldLoadCombinations;
#endif /* __cplusplus */

#endif 	/* __ldLoadCombinations_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLLoading_0000_0000 */
/* [local] */ 

#include <LoadingErrors.h>


extern RPC_IF_HANDLE __MIDL_itf_WBFLLoading_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLLoading_0000_0000_v0_0_s_ifspec;


#ifndef __WBFLLoading_LIBRARY_DEFINED__
#define __WBFLLoading_LIBRARY_DEFINED__

/* library WBFLLoading */
/* [helpstring][helpcontext][version][uuid] */ 

typedef /* [public][helpstring][uuid][public] */  DECLSPEC_UUID("B43D3508-5101-42d1-BCF0-037F79B20C98") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0001
    {
        ldctPointLoad	= 34001,
        ldctPointLoadsChanged	= 34002,
        ldctPointLoadsAdded	= 34003,
        ldctPointLoadsBeforeRemove	= 34004,
        ldctDistributedLoad	= 34005,
        ldctDistributedLoadsChanged	= 34006,
        ldctDistributedLoadsAdded	= 34007,
        ldctDistributedLoadsBeforeRemove	= 34008,
        ldctSettlementLoad	= 34009,
        ldctSettlementLoadsChanged	= 34010,
        ldctSettlementLoadsAdded	= 34011,
        ldctSettlementLoadsBeforeRemove	= 34012,
        ldctTemperatureLoad	= 34013,
        ldctTemperatureLoadsChanged	= 34014,
        ldctTemperatureLoadsAdded	= 34015,
        ldctTemperatureLoadsBeforeRemove	= 34016,
        ldctStrainLoad	= 34017,
        ldctStrainLoadsChanged	= 34018,
        ldctStrainLoadsAdded	= 34019,
        ldctStrainLoadsBeforeRemove	= 34020,
        ldctAxle	= 34021,
        ldctAxlesChanged	= 34022,
        ldctAxlesAdded	= 34023,
        ldctAxlesBeforeRemove	= 34024,
        ldctAxlesMoveTo	= 34025,
        ldctAxlesCopyTo	= 34026,
        ldctAxlesReverse	= 34027,
        ldctVehicularLoad	= 34028,
        ldctVehicularLoadsChanged	= 34029,
        ldctVehicularLoadsRenamed	= 34030,
        ldctVehicularLoadsAdded	= 34031,
        ldctVehicularLoadsBeforeRemove	= 34032,
        ldctLoadGroupChanged	= 34033,
        ldctLoadGroupRenamed	= 34034,
        ldctLoadCase	= 34035,
        ldctLoadCaseRenamed	= 34036,
        ldctLoadCasesChanged	= 34037,
        ldctLoadCasesRenamed	= 34038,
        ldctLoadCasesAdded	= 34039,
        ldctLoadCasesBeforeRemove	= 34040,
        ldctLoadGroupsChanged	= 34041,
        ldctLoadGroupsRenamed	= 34042,
        ldctLoadGroupsAdded	= 34043,
        ldctLoadGroupsBeforeRemove	= 34044,
        ldctLoadCombination	= 34045,
        ldctLoadCombinationRenamed	= 34046,
        ldctLoadCombinationsChanged	= 34047,
        ldctLoadCombinationsRenamed	= 34048,
        ldctLoadCombinationsAdded	= 34049,
        ldctLoadCombinationsBeforeRemove	= 34050
    } 	ldEventDispatchIds;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("BC4341CB-02DF-4cb8-8D4A-8C25CC2A7D6F") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0002
    {
        ldloGlobal	= 0,
        ldloMember	= 1,
        ldloGlobalProjected	= 2
    } 	ldLoadOrientation;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("52E08C79-A82A-43a8-9DA1-8563A0374EFC") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0003
    {
        ldldFx	= 0,
        ldldFy	= 1
    } 	ldLoadDirection;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("9948B8FA-0931-4cbc-B918-FFF0A43663B4") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0004
    {
        ldvcDefault	= 0,
        ldvcTruckOnly	= 1,
        ldvcLaneOnly	= 2,
        ldvcTruckPlusLane	= 3,
        ldvcTruckLaneEnvelope	= 4,
        ldvcSidewalkOnly	= 5
    } 	ldVehicularLoadConfigurationType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("4ACEBE9C-2DAD-423c-9FE1-3A9FD8D38F00") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0005
    {
        ldlaEntireStructure	= 1,
        ldlaContraflexure	= 2
    } 	ldLiveLoadApplicabilityType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("0074DD4A-3668-402b-B879-844E69DEA66C") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0006
    {
        ldltNone	= -1,
        ldltDeflection	= 0,
        ldltDesign	= 1,
        ldltPedestrian	= 2,
        ldltFatigue	= 3,
        ldltPermit	= 4,
        ldltSpecial	= 5
    } 	ldLiveLoadModelType;

typedef /* [public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("0E139A77-FBEF-4219-A251-178E3B51C9D4") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0007
    {
        ldctService	= 0,
        ldctStrength	= 1,
        ldctExtremeEvent	= 2,
        ldctFatigue	= 3,
        ldctPermit	= 4,
        ldctUserDefined	= 5
    } 	ldLoadCombinationType;

typedef /* [public][public][public][public][public][public][public][public][public][helpcontext][helpstring][uuid][public] */  DECLSPEC_UUID("04951897-BE2B-4417-9276-98850171F68F") 
enum __MIDL___MIDL_itf_WBFLLoading_0000_0000_0008
    {
        ldcgDescription	= 1,
        ldcgLiveLoad	= 2,
        ldcgUserItemData	= 3,
        ldcgLoading	= 4,
        ldcgCombination	= 5
    } 	ldLoadingChangeType;


EXTERN_C const IID LIBID_WBFLLoading;

#ifndef __ldIPointLoad_INTERFACE_DEFINED__
#define __ldIPointLoad_INTERFACE_DEFINED__

/* interface ldIPointLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A120D9E2-F773-42eb-B850-B2A0CB3BEB68")
    ldIPointLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Location( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Location( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Fy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Fy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Mz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Mz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetForce( 
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetForce( 
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIPointLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIPointLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ldIPointLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ldIPointLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Location )( 
            ldIPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Location )( 
            ldIPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fx )( 
            ldIPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fx )( 
            ldIPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Fy )( 
            ldIPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Fy )( 
            ldIPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mz )( 
            ldIPointLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Mz )( 
            ldIPointLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetForce )( 
            ldIPointLoad * This,
            /* [in] */ Float64 Fx,
            /* [in] */ Float64 Fy,
            /* [in] */ Float64 Mz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetForce )( 
            ldIPointLoad * This,
            /* [out] */ Float64 *Fx,
            /* [out] */ Float64 *Fy,
            /* [out] */ Float64 *Mz);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIPointLoad * This,
            /* [retval][out] */ ldIPointLoad **clone);
        
        END_INTERFACE
    } ldIPointLoadVtbl;

    interface ldIPointLoad
    {
        CONST_VTBL struct ldIPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIPointLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ldIPointLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ldIPointLoad_get_Location(This,pVal)	\
    ( (This)->lpVtbl -> get_Location(This,pVal) ) 

#define ldIPointLoad_put_Location(This,newVal)	\
    ( (This)->lpVtbl -> put_Location(This,newVal) ) 

#define ldIPointLoad_get_Fx(This,pVal)	\
    ( (This)->lpVtbl -> get_Fx(This,pVal) ) 

#define ldIPointLoad_put_Fx(This,newVal)	\
    ( (This)->lpVtbl -> put_Fx(This,newVal) ) 

#define ldIPointLoad_get_Fy(This,pVal)	\
    ( (This)->lpVtbl -> get_Fy(This,pVal) ) 

#define ldIPointLoad_put_Fy(This,newVal)	\
    ( (This)->lpVtbl -> put_Fy(This,newVal) ) 

#define ldIPointLoad_get_Mz(This,pVal)	\
    ( (This)->lpVtbl -> get_Mz(This,pVal) ) 

#define ldIPointLoad_put_Mz(This,newVal)	\
    ( (This)->lpVtbl -> put_Mz(This,newVal) ) 

#define ldIPointLoad_SetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> SetForce(This,Fx,Fy,Mz) ) 

#define ldIPointLoad_GetForce(This,Fx,Fy,Mz)	\
    ( (This)->lpVtbl -> GetForce(This,Fx,Fy,Mz) ) 

#define ldIPointLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIPointLoad_INTERFACE_DEFINED__ */


#ifndef __ldIPointLoadEvents_INTERFACE_DEFINED__
#define __ldIPointLoadEvents_INTERFACE_DEFINED__

/* interface ldIPointLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIPointLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FAC83784-2660-4959-A071-118006D19A3C")
    ldIPointLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadChanged( 
            /* [in] */ ldIPointLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIPointLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIPointLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIPointLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIPointLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadChanged )( 
            ldIPointLoadEvents * This,
            /* [in] */ ldIPointLoad *me);
        
        END_INTERFACE
    } ldIPointLoadEventsVtbl;

    interface ldIPointLoadEvents
    {
        CONST_VTBL struct ldIPointLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIPointLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIPointLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIPointLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIPointLoadEvents_OnPointLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnPointLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIPointLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldIPointLoadItem_INTERFACE_DEFINED__
#define __ldIPointLoadItem_INTERFACE_DEFINED__

/* interface ldIPointLoadItem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIPointLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("005CD59D-421D-4a6b-AE08-F0E9F5EBBAA4")
    ldIPointLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ldIPointLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIPointLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIPointLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIPointLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIPointLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ldIPointLoadItem * This,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ldIPointLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ldIPointLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIPointLoadItem * This,
            /* [retval][out] */ ldIPointLoad **pVal);
        
        END_INTERFACE
    } ldIPointLoadItemVtbl;

    interface ldIPointLoadItem
    {
        CONST_VTBL struct ldIPointLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIPointLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIPointLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIPointLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIPointLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ldIPointLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ldIPointLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ldIPointLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIPointLoadItem_INTERFACE_DEFINED__ */


#ifndef __ldIEnumPointLoad_INTERFACE_DEFINED__
#define __ldIEnumPointLoad_INTERFACE_DEFINED__

/* interface ldIEnumPointLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumPointLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("465E3AEB-5331-42c5-9025-3F461CA9A588")
    ldIEnumPointLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumPointLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldIPointLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumPointLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumPointLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumPointLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumPointLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumPointLoad * This,
            /* [out] */ ldIEnumPointLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumPointLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldIPointLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumPointLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumPointLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumPointLoadVtbl;

    interface ldIEnumPointLoad
    {
        CONST_VTBL struct ldIEnumPointLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumPointLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumPointLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumPointLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumPointLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumPointLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumPointLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumPointLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumPointLoad_INTERFACE_DEFINED__ */


#ifndef __ldIPointLoads_INTERFACE_DEFINED__
#define __ldIPointLoads_INTERFACE_DEFINED__

/* interface ldIPointLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIPointLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A1E2A58-167A-4e42-ADC5-B33BE28BBE1F")
    ldIPointLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIPointLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIPointLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ IDType ID,
            /* [in] */ ldIPointLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumPointLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIPointLoad *Load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIPointLoadItem **__MIDL__ldIPointLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ IDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIPointLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIPointLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIPointLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIPointLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIPointLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIPointLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldIPointLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldIPointLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIPointLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIPointLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIPointLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ldIPointLoads * This,
            /* [in] */ IDType ID,
            /* [in] */ ldIPointLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldIPointLoads * This,
            /* [retval][out] */ ldIEnumPointLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldIPointLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIPointLoad *Load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldIPointLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIPointLoadItem **__MIDL__ldIPointLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ldIPointLoads * This,
            /* [in] */ IDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldIPointLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ldIPointLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIPointLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIPointLoads * This,
            /* [retval][out] */ ldIPointLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldIPointLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ldIPointLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldIPointLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ldIPointLoadsVtbl;

    interface ldIPointLoads
    {
        CONST_VTBL struct ldIPointLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIPointLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIPointLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIPointLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIPointLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldIPointLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldIPointLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ldIPointLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ldIPointLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldIPointLoads_Add(This,Stage,LoadGroup,Load)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load) ) 

#define ldIPointLoads_Find(This,ID,__MIDL__ldIPointLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ldIPointLoads0000) ) 

#define ldIPointLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ldIPointLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ldIPointLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ldIPointLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldIPointLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldIPointLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ldIPointLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIPointLoads_INTERFACE_DEFINED__ */


#ifndef __ldIPointLoadsEvents_INTERFACE_DEFINED__
#define __ldIPointLoadsEvents_INTERFACE_DEFINED__

/* interface ldIPointLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIPointLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("407BD607-CD35-4f1e-9B84-706252D2CE55")
    ldIPointLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadChanged( 
            /* [in] */ ldIPointLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadAdded( 
            /* [in] */ ldIPointLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnPointLoadRemoved( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIPointLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIPointLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIPointLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIPointLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadChanged )( 
            ldIPointLoadsEvents * This,
            /* [in] */ ldIPointLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadAdded )( 
            ldIPointLoadsEvents * This,
            /* [in] */ ldIPointLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnPointLoadRemoved )( 
            ldIPointLoadsEvents * This);
        
        END_INTERFACE
    } ldIPointLoadsEventsVtbl;

    interface ldIPointLoadsEvents
    {
        CONST_VTBL struct ldIPointLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIPointLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIPointLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIPointLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIPointLoadsEvents_OnPointLoadChanged(This,load)	\
    ( (This)->lpVtbl -> OnPointLoadChanged(This,load) ) 

#define ldIPointLoadsEvents_OnPointLoadAdded(This,load)	\
    ( (This)->lpVtbl -> OnPointLoadAdded(This,load) ) 

#define ldIPointLoadsEvents_OnPointLoadRemoved(This)	\
    ( (This)->lpVtbl -> OnPointLoadRemoved(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIPointLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldIDistributedLoad_INTERFACE_DEFINED__
#define __ldIDistributedLoad_INTERFACE_DEFINED__

/* interface ldIDistributedLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB64F919-CF8F-4d9b-89DC-48F5E7A524DA")
    ldIDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIDistributedLoad **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ ldLoadOrientation *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ ldLoadOrientation newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Direction( 
            /* [retval][out] */ ldLoadDirection *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Direction( 
            /* [in] */ ldLoadDirection newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WStart( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WStart( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WEnd( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WEnd( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StartLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_StartLocation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EndLocation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EndLocation( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ ldIDistributedLoad **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ ldLoadOrientation *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            ldIDistributedLoad * This,
            /* [in] */ ldLoadOrientation newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Direction )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ ldLoadDirection *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Direction )( 
            ldIDistributedLoad * This,
            /* [in] */ ldLoadDirection newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WStart )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WStart )( 
            ldIDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WEnd )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WEnd )( 
            ldIDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ldIDistributedLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartLocation )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartLocation )( 
            ldIDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EndLocation )( 
            ldIDistributedLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EndLocation )( 
            ldIDistributedLoad * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } ldIDistributedLoadVtbl;

    interface ldIDistributedLoad
    {
        CONST_VTBL struct ldIDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIDistributedLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldIDistributedLoad_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define ldIDistributedLoad_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define ldIDistributedLoad_get_Direction(This,pVal)	\
    ( (This)->lpVtbl -> get_Direction(This,pVal) ) 

#define ldIDistributedLoad_put_Direction(This,newVal)	\
    ( (This)->lpVtbl -> put_Direction(This,newVal) ) 

#define ldIDistributedLoad_get_WStart(This,pVal)	\
    ( (This)->lpVtbl -> get_WStart(This,pVal) ) 

#define ldIDistributedLoad_put_WStart(This,newVal)	\
    ( (This)->lpVtbl -> put_WStart(This,newVal) ) 

#define ldIDistributedLoad_get_WEnd(This,pVal)	\
    ( (This)->lpVtbl -> get_WEnd(This,pVal) ) 

#define ldIDistributedLoad_put_WEnd(This,newVal)	\
    ( (This)->lpVtbl -> put_WEnd(This,newVal) ) 

#define ldIDistributedLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ldIDistributedLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ldIDistributedLoad_get_StartLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_StartLocation(This,pVal) ) 

#define ldIDistributedLoad_put_StartLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_StartLocation(This,newVal) ) 

#define ldIDistributedLoad_get_EndLocation(This,pVal)	\
    ( (This)->lpVtbl -> get_EndLocation(This,pVal) ) 

#define ldIDistributedLoad_put_EndLocation(This,newVal)	\
    ( (This)->lpVtbl -> put_EndLocation(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __ldIDistributedLoadEvents_INTERFACE_DEFINED__
#define __ldIDistributedLoadEvents_INTERFACE_DEFINED__

/* interface ldIDistributedLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIDistributedLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C015F31-4A82-46a9-80BB-CE93838869D8")
    ldIDistributedLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadChanged( 
            /* [in] */ ldIDistributedLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIDistributedLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIDistributedLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIDistributedLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIDistributedLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadChanged )( 
            ldIDistributedLoadEvents * This,
            /* [in] */ ldIDistributedLoad *me);
        
        END_INTERFACE
    } ldIDistributedLoadEventsVtbl;

    interface ldIDistributedLoadEvents
    {
        CONST_VTBL struct ldIDistributedLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIDistributedLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIDistributedLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIDistributedLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIDistributedLoadEvents_OnDistributedLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnDistributedLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIDistributedLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldIDistributedLoadItem_INTERFACE_DEFINED__
#define __ldIDistributedLoadItem_INTERFACE_DEFINED__

/* interface ldIDistributedLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIDistributedLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1570438-0F78-4892-8EA8-523C0120F37E")
    ldIDistributedLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ldIDistributedLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIDistributedLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIDistributedLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIDistributedLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIDistributedLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ldIDistributedLoadItem * This,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ldIDistributedLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ldIDistributedLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIDistributedLoadItem * This,
            /* [retval][out] */ ldIDistributedLoad **pVal);
        
        END_INTERFACE
    } ldIDistributedLoadItemVtbl;

    interface ldIDistributedLoadItem
    {
        CONST_VTBL struct ldIDistributedLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIDistributedLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIDistributedLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIDistributedLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIDistributedLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ldIDistributedLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ldIDistributedLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ldIDistributedLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIDistributedLoadItem_INTERFACE_DEFINED__ */


#ifndef __ldIEnumDistributedLoad_INTERFACE_DEFINED__
#define __ldIEnumDistributedLoad_INTERFACE_DEFINED__

/* interface ldIEnumDistributedLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumDistributedLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD719FBA-9CFD-4e9f-B2A3-5EB77AB39DE7")
    ldIEnumDistributedLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumDistributedLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldIDistributedLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumDistributedLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumDistributedLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumDistributedLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumDistributedLoad * This,
            /* [out] */ ldIEnumDistributedLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumDistributedLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldIDistributedLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumDistributedLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumDistributedLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumDistributedLoadVtbl;

    interface ldIEnumDistributedLoad
    {
        CONST_VTBL struct ldIEnumDistributedLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumDistributedLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumDistributedLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumDistributedLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumDistributedLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumDistributedLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumDistributedLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumDistributedLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumDistributedLoad_INTERFACE_DEFINED__ */


#ifndef __ldIDistributedLoads_INTERFACE_DEFINED__
#define __ldIDistributedLoads_INTERFACE_DEFINED__

/* interface ldIDistributedLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIDistributedLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("223EE82D-8372-4012-8F71-481F8A8ADA56")
    ldIDistributedLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIDistributedLoadItem **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIDistributedLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ IDType ID,
            /* [in] */ ldIDistributedLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumDistributedLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIDistributedLoad *Load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIDistributedLoadItem **__MIDL__ldIDistributedLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ IDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIDistributedLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIDistributedLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIDistributedLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIDistributedLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIDistributedLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIDistributedLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldIDistributedLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIDistributedLoadItem **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldIDistributedLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldIDistributedLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIDistributedLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIDistributedLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ldIDistributedLoads * This,
            /* [in] */ IDType ID,
            /* [in] */ ldIDistributedLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldIDistributedLoads * This,
            /* [retval][out] */ ldIEnumDistributedLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldIDistributedLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIDistributedLoad *Load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldIDistributedLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIDistributedLoadItem **__MIDL__ldIDistributedLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ldIDistributedLoads * This,
            /* [in] */ IDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldIDistributedLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ldIDistributedLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIDistributedLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIDistributedLoads * This,
            /* [retval][out] */ ldIDistributedLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldIDistributedLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ldIDistributedLoads * This,
            /* [in] */ BSTR stage);
        
        END_INTERFACE
    } ldIDistributedLoadsVtbl;

    interface ldIDistributedLoads
    {
        CONST_VTBL struct ldIDistributedLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIDistributedLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIDistributedLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIDistributedLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIDistributedLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldIDistributedLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldIDistributedLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldIDistributedLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ldIDistributedLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ldIDistributedLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldIDistributedLoads_Add(This,Stage,LoadGroup,Load)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load) ) 

#define ldIDistributedLoads_Find(This,ID,__MIDL__ldIDistributedLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ldIDistributedLoads0000) ) 

#define ldIDistributedLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ldIDistributedLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ldIDistributedLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ldIDistributedLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldIDistributedLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldIDistributedLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIDistributedLoads_INTERFACE_DEFINED__ */


#ifndef __ldIDistributedLoadsEvents_INTERFACE_DEFINED__
#define __ldIDistributedLoadsEvents_INTERFACE_DEFINED__

/* interface ldIDistributedLoadsEvents */
/* [helpcontext][helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIDistributedLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B19B5D2C-E84D-4168-9B76-F3A83B23A8B3")
    ldIDistributedLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsChanged( 
            /* [in] */ ldIDistributedLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsAdded( 
            /* [in] */ ldIDistributedLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnDistributedLoadsBeforeRemove( 
            /* [in] */ ldIDistributedLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIDistributedLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIDistributedLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIDistributedLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIDistributedLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsChanged )( 
            ldIDistributedLoadsEvents * This,
            /* [in] */ ldIDistributedLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsAdded )( 
            ldIDistributedLoadsEvents * This,
            /* [in] */ ldIDistributedLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDistributedLoadsBeforeRemove )( 
            ldIDistributedLoadsEvents * This,
            /* [in] */ ldIDistributedLoadItem *load);
        
        END_INTERFACE
    } ldIDistributedLoadsEventsVtbl;

    interface ldIDistributedLoadsEvents
    {
        CONST_VTBL struct ldIDistributedLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIDistributedLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIDistributedLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIDistributedLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIDistributedLoadsEvents_OnDistributedLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsChanged(This,load) ) 

#define ldIDistributedLoadsEvents_OnDistributedLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsAdded(This,load) ) 

#define ldIDistributedLoadsEvents_OnDistributedLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnDistributedLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIDistributedLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldISettlementLoad_INTERFACE_DEFINED__
#define __ldISettlementLoad_INTERFACE_DEFINED__

/* interface ldISettlementLoad */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldISettlementLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DFE327FD-146E-4552-9A18-440C65A47A31")
    ldISettlementLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Rz( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Rz( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldISettlementLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldISettlementLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldISettlementLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldISettlementLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldISettlementLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ldISettlementLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ldISettlementLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dx )( 
            ldISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dx )( 
            ldISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dy )( 
            ldISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dy )( 
            ldISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Rz )( 
            ldISettlementLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Rz )( 
            ldISettlementLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldISettlementLoad * This,
            /* [retval][out] */ ldISettlementLoad **clone);
        
        END_INTERFACE
    } ldISettlementLoadVtbl;

    interface ldISettlementLoad
    {
        CONST_VTBL struct ldISettlementLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldISettlementLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldISettlementLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldISettlementLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldISettlementLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ldISettlementLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ldISettlementLoad_get_Dx(This,pVal)	\
    ( (This)->lpVtbl -> get_Dx(This,pVal) ) 

#define ldISettlementLoad_put_Dx(This,newVal)	\
    ( (This)->lpVtbl -> put_Dx(This,newVal) ) 

#define ldISettlementLoad_get_Dy(This,pVal)	\
    ( (This)->lpVtbl -> get_Dy(This,pVal) ) 

#define ldISettlementLoad_put_Dy(This,newVal)	\
    ( (This)->lpVtbl -> put_Dy(This,newVal) ) 

#define ldISettlementLoad_get_Rz(This,pVal)	\
    ( (This)->lpVtbl -> get_Rz(This,pVal) ) 

#define ldISettlementLoad_put_Rz(This,newVal)	\
    ( (This)->lpVtbl -> put_Rz(This,newVal) ) 

#define ldISettlementLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldISettlementLoad_INTERFACE_DEFINED__ */


#ifndef __ldISettlementLoadEvents_INTERFACE_DEFINED__
#define __ldISettlementLoadEvents_INTERFACE_DEFINED__

/* interface ldISettlementLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldISettlementLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BF88B56C-66D8-4d9f-82FB-3B8C3C3435A3")
    ldISettlementLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadChanged( 
            /* [in] */ ldISettlementLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldISettlementLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldISettlementLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldISettlementLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldISettlementLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadChanged )( 
            ldISettlementLoadEvents * This,
            /* [in] */ ldISettlementLoad *me);
        
        END_INTERFACE
    } ldISettlementLoadEventsVtbl;

    interface ldISettlementLoadEvents
    {
        CONST_VTBL struct ldISettlementLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldISettlementLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldISettlementLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldISettlementLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldISettlementLoadEvents_OnSettlementLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnSettlementLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldISettlementLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldISettlementLoadItem_INTERFACE_DEFINED__
#define __ldISettlementLoadItem_INTERFACE_DEFINED__

/* interface ldISettlementLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldISettlementLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00AAF5BE-CF2E-40a1-9804-68BA189F85FA")
    ldISettlementLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ldISettlementLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldISettlementLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldISettlementLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldISettlementLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldISettlementLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ldISettlementLoadItem * This,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ldISettlementLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ldISettlementLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldISettlementLoadItem * This,
            /* [retval][out] */ ldISettlementLoad **pVal);
        
        END_INTERFACE
    } ldISettlementLoadItemVtbl;

    interface ldISettlementLoadItem
    {
        CONST_VTBL struct ldISettlementLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldISettlementLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldISettlementLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldISettlementLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldISettlementLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ldISettlementLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ldISettlementLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ldISettlementLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldISettlementLoadItem_INTERFACE_DEFINED__ */


#ifndef __ldIEnumSettlementLoad_INTERFACE_DEFINED__
#define __ldIEnumSettlementLoad_INTERFACE_DEFINED__

/* interface ldIEnumSettlementLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumSettlementLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C19D1F3-AA0F-4d54-9B35-59F67EBFBA86")
    ldIEnumSettlementLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumSettlementLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldISettlementLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumSettlementLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumSettlementLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumSettlementLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumSettlementLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumSettlementLoad * This,
            /* [out] */ ldIEnumSettlementLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumSettlementLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldISettlementLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumSettlementLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumSettlementLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumSettlementLoadVtbl;

    interface ldIEnumSettlementLoad
    {
        CONST_VTBL struct ldIEnumSettlementLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumSettlementLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumSettlementLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumSettlementLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumSettlementLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumSettlementLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumSettlementLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumSettlementLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumSettlementLoad_INTERFACE_DEFINED__ */


#ifndef __ldISettlementLoads_INTERFACE_DEFINED__
#define __ldISettlementLoads_INTERFACE_DEFINED__

/* interface ldISettlementLoads */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldISettlementLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("988D8ACE-37DB-4857-A1B1-3178F84B24DA")
    ldISettlementLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldISettlementLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldISettlementLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ IDType ID,
            /* [in] */ ldISettlementLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumSettlementLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldISettlementLoad *Load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldISettlementLoadItem **__MIDL__ldISettlementLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ IDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldISettlementLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldISettlementLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldISettlementLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldISettlementLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldISettlementLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldISettlementLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldISettlementLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldISettlementLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldISettlementLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldISettlementLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldISettlementLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ldISettlementLoads * This,
            /* [in] */ IDType ID,
            /* [in] */ ldISettlementLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldISettlementLoads * This,
            /* [retval][out] */ ldIEnumSettlementLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldISettlementLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldISettlementLoad *Load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldISettlementLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldISettlementLoadItem **__MIDL__ldISettlementLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ldISettlementLoads * This,
            /* [in] */ IDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldISettlementLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ldISettlementLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldISettlementLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldISettlementLoads * This,
            /* [retval][out] */ ldISettlementLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldISettlementLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ldISettlementLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldISettlementLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ldISettlementLoadsVtbl;

    interface ldISettlementLoads
    {
        CONST_VTBL struct ldISettlementLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldISettlementLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldISettlementLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldISettlementLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldISettlementLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldISettlementLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldISettlementLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ldISettlementLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ldISettlementLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldISettlementLoads_Add(This,Stage,LoadGroup,Load)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load) ) 

#define ldISettlementLoads_Find(This,ID,__MIDL__ldISettlementLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ldISettlementLoads0000) ) 

#define ldISettlementLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ldISettlementLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ldISettlementLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ldISettlementLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldISettlementLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldISettlementLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ldISettlementLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldISettlementLoads_INTERFACE_DEFINED__ */


#ifndef __ldISettlementLoadsEvents_INTERFACE_DEFINED__
#define __ldISettlementLoadsEvents_INTERFACE_DEFINED__

/* interface ldISettlementLoadsEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldISettlementLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5B0A356B-D586-44bb-9805-7747F3FED248")
    ldISettlementLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsChanged( 
            /* [in] */ ldISettlementLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsAdded( 
            /* [in] */ ldISettlementLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnSettlementLoadsBeforeRemove( 
            /* [in] */ ldISettlementLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldISettlementLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldISettlementLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldISettlementLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldISettlementLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsChanged )( 
            ldISettlementLoadsEvents * This,
            /* [in] */ ldISettlementLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsAdded )( 
            ldISettlementLoadsEvents * This,
            /* [in] */ ldISettlementLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSettlementLoadsBeforeRemove )( 
            ldISettlementLoadsEvents * This,
            /* [in] */ ldISettlementLoadItem *load);
        
        END_INTERFACE
    } ldISettlementLoadsEventsVtbl;

    interface ldISettlementLoadsEvents
    {
        CONST_VTBL struct ldISettlementLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldISettlementLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldISettlementLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldISettlementLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldISettlementLoadsEvents_OnSettlementLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsChanged(This,load) ) 

#define ldISettlementLoadsEvents_OnSettlementLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsAdded(This,load) ) 

#define ldISettlementLoadsEvents_OnSettlementLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnSettlementLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldISettlementLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldITemperatureLoad_INTERFACE_DEFINED__
#define __ldITemperatureLoad_INTERFACE_DEFINED__

/* interface ldITemperatureLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldITemperatureLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED6DC322-3F7A-44ec-80A8-95511454AB87")
    ldITemperatureLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TTop( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TTop( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TBottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TBottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldITemperatureLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldITemperatureLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldITemperatureLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldITemperatureLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldITemperatureLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ldITemperatureLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ldITemperatureLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TTop )( 
            ldITemperatureLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TTop )( 
            ldITemperatureLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TBottom )( 
            ldITemperatureLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TBottom )( 
            ldITemperatureLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldITemperatureLoad * This,
            /* [retval][out] */ ldITemperatureLoad **clone);
        
        END_INTERFACE
    } ldITemperatureLoadVtbl;

    interface ldITemperatureLoad
    {
        CONST_VTBL struct ldITemperatureLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldITemperatureLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldITemperatureLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldITemperatureLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldITemperatureLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ldITemperatureLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ldITemperatureLoad_get_TTop(This,pVal)	\
    ( (This)->lpVtbl -> get_TTop(This,pVal) ) 

#define ldITemperatureLoad_put_TTop(This,newVal)	\
    ( (This)->lpVtbl -> put_TTop(This,newVal) ) 

#define ldITemperatureLoad_get_TBottom(This,pVal)	\
    ( (This)->lpVtbl -> get_TBottom(This,pVal) ) 

#define ldITemperatureLoad_put_TBottom(This,newVal)	\
    ( (This)->lpVtbl -> put_TBottom(This,newVal) ) 

#define ldITemperatureLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldITemperatureLoad_INTERFACE_DEFINED__ */


#ifndef __ldITemperatureLoadEvents_INTERFACE_DEFINED__
#define __ldITemperatureLoadEvents_INTERFACE_DEFINED__

/* interface ldITemperatureLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldITemperatureLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E25FA1F-2E3F-402f-8763-597B22154FC0")
    ldITemperatureLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadChanged( 
            /* [in] */ ldITemperatureLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldITemperatureLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldITemperatureLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldITemperatureLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldITemperatureLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadChanged )( 
            ldITemperatureLoadEvents * This,
            /* [in] */ ldITemperatureLoad *me);
        
        END_INTERFACE
    } ldITemperatureLoadEventsVtbl;

    interface ldITemperatureLoadEvents
    {
        CONST_VTBL struct ldITemperatureLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldITemperatureLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldITemperatureLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldITemperatureLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldITemperatureLoadEvents_OnTemperatureLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnTemperatureLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldITemperatureLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldITemperatureLoadItem_INTERFACE_DEFINED__
#define __ldITemperatureLoadItem_INTERFACE_DEFINED__

/* interface ldITemperatureLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldITemperatureLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BBBDCA6-C8E6-45fb-B918-87313D854D5C")
    ldITemperatureLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ldITemperatureLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldITemperatureLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldITemperatureLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldITemperatureLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldITemperatureLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ldITemperatureLoadItem * This,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ldITemperatureLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ldITemperatureLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldITemperatureLoadItem * This,
            /* [retval][out] */ ldITemperatureLoad **pVal);
        
        END_INTERFACE
    } ldITemperatureLoadItemVtbl;

    interface ldITemperatureLoadItem
    {
        CONST_VTBL struct ldITemperatureLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldITemperatureLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldITemperatureLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldITemperatureLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldITemperatureLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ldITemperatureLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ldITemperatureLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ldITemperatureLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldITemperatureLoadItem_INTERFACE_DEFINED__ */


#ifndef __ldIEnumTemperatureLoad_INTERFACE_DEFINED__
#define __ldIEnumTemperatureLoad_INTERFACE_DEFINED__

/* interface ldIEnumTemperatureLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumTemperatureLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01D84B2D-7BBE-4d10-88AE-9E433FE2C90E")
    ldIEnumTemperatureLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumTemperatureLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldITemperatureLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumTemperatureLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumTemperatureLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumTemperatureLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumTemperatureLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumTemperatureLoad * This,
            /* [out] */ ldIEnumTemperatureLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumTemperatureLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldITemperatureLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumTemperatureLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumTemperatureLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumTemperatureLoadVtbl;

    interface ldIEnumTemperatureLoad
    {
        CONST_VTBL struct ldIEnumTemperatureLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumTemperatureLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumTemperatureLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumTemperatureLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumTemperatureLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumTemperatureLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumTemperatureLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumTemperatureLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumTemperatureLoad_INTERFACE_DEFINED__ */


#ifndef __ldITemperatureLoads_INTERFACE_DEFINED__
#define __ldITemperatureLoads_INTERFACE_DEFINED__

/* interface ldITemperatureLoads */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldITemperatureLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BD2129C3-8B72-4316-9AE5-C04B79A0B946")
    ldITemperatureLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldITemperatureLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldITemperatureLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ IDType ID,
            /* [in] */ ldITemperatureLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumTemperatureLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldITemperatureLoad *Load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldITemperatureLoadItem **__MIDL__ldITemperatureLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ IDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldITemperatureLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldITemperatureLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldITemperatureLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldITemperatureLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldITemperatureLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldITemperatureLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldITemperatureLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldITemperatureLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldITemperatureLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldITemperatureLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldITemperatureLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ldITemperatureLoads * This,
            /* [in] */ IDType ID,
            /* [in] */ ldITemperatureLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldITemperatureLoads * This,
            /* [retval][out] */ ldIEnumTemperatureLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldITemperatureLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldITemperatureLoad *Load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldITemperatureLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldITemperatureLoadItem **__MIDL__ldITemperatureLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ldITemperatureLoads * This,
            /* [in] */ IDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldITemperatureLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ldITemperatureLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldITemperatureLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldITemperatureLoads * This,
            /* [retval][out] */ ldITemperatureLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldITemperatureLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ldITemperatureLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldITemperatureLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ldITemperatureLoadsVtbl;

    interface ldITemperatureLoads
    {
        CONST_VTBL struct ldITemperatureLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldITemperatureLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldITemperatureLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldITemperatureLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldITemperatureLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldITemperatureLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldITemperatureLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ldITemperatureLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ldITemperatureLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldITemperatureLoads_Add(This,Stage,LoadGroup,Load)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load) ) 

#define ldITemperatureLoads_Find(This,ID,__MIDL__ldITemperatureLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ldITemperatureLoads0000) ) 

#define ldITemperatureLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ldITemperatureLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ldITemperatureLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ldITemperatureLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldITemperatureLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldITemperatureLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ldITemperatureLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldITemperatureLoads_INTERFACE_DEFINED__ */


#ifndef __ldITemperatureLoadsEvents_INTERFACE_DEFINED__
#define __ldITemperatureLoadsEvents_INTERFACE_DEFINED__

/* interface ldITemperatureLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldITemperatureLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2BB974FC-B438-4cb2-939D-E3ED7BBAD2C2")
    ldITemperatureLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsChanged( 
            /* [in] */ ldITemperatureLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsAdded( 
            /* [in] */ ldITemperatureLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnTemperatureLoadsBeforeRemove( 
            /* [in] */ ldITemperatureLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldITemperatureLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldITemperatureLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldITemperatureLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldITemperatureLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsChanged )( 
            ldITemperatureLoadsEvents * This,
            /* [in] */ ldITemperatureLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsAdded )( 
            ldITemperatureLoadsEvents * This,
            /* [in] */ ldITemperatureLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTemperatureLoadsBeforeRemove )( 
            ldITemperatureLoadsEvents * This,
            /* [in] */ ldITemperatureLoadItem *load);
        
        END_INTERFACE
    } ldITemperatureLoadsEventsVtbl;

    interface ldITemperatureLoadsEvents
    {
        CONST_VTBL struct ldITemperatureLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldITemperatureLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldITemperatureLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldITemperatureLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldITemperatureLoadsEvents_OnTemperatureLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsChanged(This,load) ) 

#define ldITemperatureLoadsEvents_OnTemperatureLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsAdded(This,load) ) 

#define ldITemperatureLoadsEvents_OnTemperatureLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnTemperatureLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldITemperatureLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldIStrainLoad_INTERFACE_DEFINED__
#define __ldIStrainLoad_INTERFACE_DEFINED__

/* interface ldIStrainLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIStrainLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1F8ABAFE-0226-442d-85DC-4C0B2A7F214C")
    ldIStrainLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MemberID( 
            /* [retval][out] */ MemberIDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MemberID( 
            /* [in] */ MemberIDType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AxialStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AxialStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CurvatureStrain( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CurvatureStrain( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIStrainLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIStrainLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIStrainLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIStrainLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIStrainLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MemberID )( 
            ldIStrainLoad * This,
            /* [retval][out] */ MemberIDType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MemberID )( 
            ldIStrainLoad * This,
            /* [in] */ MemberIDType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AxialStrain )( 
            ldIStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AxialStrain )( 
            ldIStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurvatureStrain )( 
            ldIStrainLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurvatureStrain )( 
            ldIStrainLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIStrainLoad * This,
            /* [retval][out] */ ldIStrainLoad **clone);
        
        END_INTERFACE
    } ldIStrainLoadVtbl;

    interface ldIStrainLoad
    {
        CONST_VTBL struct ldIStrainLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIStrainLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIStrainLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIStrainLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIStrainLoad_get_MemberID(This,pVal)	\
    ( (This)->lpVtbl -> get_MemberID(This,pVal) ) 

#define ldIStrainLoad_put_MemberID(This,newVal)	\
    ( (This)->lpVtbl -> put_MemberID(This,newVal) ) 

#define ldIStrainLoad_get_AxialStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_AxialStrain(This,pVal) ) 

#define ldIStrainLoad_put_AxialStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_AxialStrain(This,newVal) ) 

#define ldIStrainLoad_get_CurvatureStrain(This,pVal)	\
    ( (This)->lpVtbl -> get_CurvatureStrain(This,pVal) ) 

#define ldIStrainLoad_put_CurvatureStrain(This,newVal)	\
    ( (This)->lpVtbl -> put_CurvatureStrain(This,newVal) ) 

#define ldIStrainLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIStrainLoad_INTERFACE_DEFINED__ */


#ifndef __ldIStrainLoadEvents_INTERFACE_DEFINED__
#define __ldIStrainLoadEvents_INTERFACE_DEFINED__

/* interface ldIStrainLoadEvents */
/* [helpstring][unique][helpcontext][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIStrainLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ADA08034-632D-46e1-B448-F4BF4050DCAF")
    ldIStrainLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadChanged( 
            /* [in] */ ldIStrainLoad *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIStrainLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIStrainLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIStrainLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIStrainLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadChanged )( 
            ldIStrainLoadEvents * This,
            /* [in] */ ldIStrainLoad *me);
        
        END_INTERFACE
    } ldIStrainLoadEventsVtbl;

    interface ldIStrainLoadEvents
    {
        CONST_VTBL struct ldIStrainLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIStrainLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIStrainLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIStrainLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIStrainLoadEvents_OnStrainLoadChanged(This,me)	\
    ( (This)->lpVtbl -> OnStrainLoadChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIStrainLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldIStrainLoadItem_INTERFACE_DEFINED__
#define __ldIStrainLoadItem_INTERFACE_DEFINED__

/* interface ldIStrainLoadItem */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIStrainLoadItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A8AF11BB-B98F-4076-91C9-B8A8547574F9")
    ldIStrainLoadItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ IDType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Stage( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroup( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [retval][out] */ ldIStrainLoad **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIStrainLoadItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIStrainLoadItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIStrainLoadItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIStrainLoadItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ID )( 
            ldIStrainLoadItem * This,
            /* [retval][out] */ IDType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Stage )( 
            ldIStrainLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroup )( 
            ldIStrainLoadItem * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIStrainLoadItem * This,
            /* [retval][out] */ ldIStrainLoad **pVal);
        
        END_INTERFACE
    } ldIStrainLoadItemVtbl;

    interface ldIStrainLoadItem
    {
        CONST_VTBL struct ldIStrainLoadItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIStrainLoadItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIStrainLoadItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIStrainLoadItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIStrainLoadItem_get_ID(This,pVal)	\
    ( (This)->lpVtbl -> get_ID(This,pVal) ) 

#define ldIStrainLoadItem_get_Stage(This,pVal)	\
    ( (This)->lpVtbl -> get_Stage(This,pVal) ) 

#define ldIStrainLoadItem_get_LoadGroup(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroup(This,pVal) ) 

#define ldIStrainLoadItem_get_Load(This,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIStrainLoadItem_INTERFACE_DEFINED__ */


#ifndef __ldIEnumStrainLoad_INTERFACE_DEFINED__
#define __ldIEnumStrainLoad_INTERFACE_DEFINED__

/* interface ldIEnumStrainLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumStrainLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35425A18-0CA0-416f-98B3-AAA075BA5293")
    ldIEnumStrainLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumStrainLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldIStrainLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumStrainLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumStrainLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumStrainLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumStrainLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumStrainLoad * This,
            /* [out] */ ldIEnumStrainLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumStrainLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldIStrainLoadItem **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumStrainLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumStrainLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumStrainLoadVtbl;

    interface ldIEnumStrainLoad
    {
        CONST_VTBL struct ldIEnumStrainLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumStrainLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumStrainLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumStrainLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumStrainLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumStrainLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumStrainLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumStrainLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumStrainLoad_INTERFACE_DEFINED__ */


#ifndef __ldIStrainLoads_INTERFACE_DEFINED__
#define __ldIStrainLoads_INTERFACE_DEFINED__

/* interface ldIStrainLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIStrainLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CF883D0-394D-4f16-A688-FE12596CFF66")
    ldIStrainLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIStrainLoadItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Load( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIStrainLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Load( 
            /* [in] */ IDType ID,
            /* [in] */ ldIStrainLoad *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumStrainLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIStrainLoad *Load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIStrainLoadItem **__MIDL__ldIStrainLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByID( 
            /* [in] */ IDType ID) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE FilterByStageGroup( 
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIStrainLoads **filteredcoll) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIStrainLoads **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveStage( 
            /* [in] */ BSTR stage) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIStrainLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIStrainLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIStrainLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIStrainLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldIStrainLoads * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldIStrainLoads * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldIStrainLoadItem **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Load )( 
            ldIStrainLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIStrainLoad **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Load )( 
            ldIStrainLoads * This,
            /* [in] */ IDType ID,
            /* [in] */ ldIStrainLoad *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldIStrainLoads * This,
            /* [retval][out] */ ldIEnumStrainLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldIStrainLoads * This,
            /* [in] */ BSTR Stage,
            /* [in] */ BSTR LoadGroup,
            /* [in] */ ldIStrainLoad *Load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldIStrainLoads * This,
            /* [in] */ IDType ID,
            /* [retval][out] */ ldIStrainLoadItem **__MIDL__ldIStrainLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByID )( 
            ldIStrainLoads * This,
            /* [in] */ IDType ID);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldIStrainLoads * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilterByStageGroup )( 
            ldIStrainLoads * This,
            /* [in] */ BSTR stage,
            /* [in] */ BSTR loadgroup,
            /* [retval][out] */ ldIStrainLoads **filteredcoll);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIStrainLoads * This,
            /* [retval][out] */ ldIStrainLoads **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldIStrainLoads * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveStage )( 
            ldIStrainLoads * This,
            /* [in] */ BSTR stage);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldIStrainLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        END_INTERFACE
    } ldIStrainLoadsVtbl;

    interface ldIStrainLoads
    {
        CONST_VTBL struct ldIStrainLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIStrainLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIStrainLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIStrainLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIStrainLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldIStrainLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldIStrainLoads_get_Load(This,ID,pVal)	\
    ( (This)->lpVtbl -> get_Load(This,ID,pVal) ) 

#define ldIStrainLoads_putref_Load(This,ID,newVal)	\
    ( (This)->lpVtbl -> putref_Load(This,ID,newVal) ) 

#define ldIStrainLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldIStrainLoads_Add(This,Stage,LoadGroup,Load)	\
    ( (This)->lpVtbl -> Add(This,Stage,LoadGroup,Load) ) 

#define ldIStrainLoads_Find(This,ID,__MIDL__ldIStrainLoads0000)	\
    ( (This)->lpVtbl -> Find(This,ID,__MIDL__ldIStrainLoads0000) ) 

#define ldIStrainLoads_RemoveByID(This,ID)	\
    ( (This)->lpVtbl -> RemoveByID(This,ID) ) 

#define ldIStrainLoads_RemoveByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index) ) 

#define ldIStrainLoads_FilterByStageGroup(This,stage,loadgroup,filteredcoll)	\
    ( (This)->lpVtbl -> FilterByStageGroup(This,stage,loadgroup,filteredcoll) ) 

#define ldIStrainLoads_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldIStrainLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldIStrainLoads_RemoveStage(This,stage)	\
    ( (This)->lpVtbl -> RemoveStage(This,stage) ) 

#define ldIStrainLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIStrainLoads_INTERFACE_DEFINED__ */


#ifndef __ldIStrainLoadsEvents_INTERFACE_DEFINED__
#define __ldIStrainLoadsEvents_INTERFACE_DEFINED__

/* interface ldIStrainLoadsEvents */
/* [helpstring][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIStrainLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3836DBE-BD64-47f8-930C-702B265059B3")
    ldIStrainLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsChanged( 
            /* [in] */ ldIStrainLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsAdded( 
            /* [in] */ ldIStrainLoadItem *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnStrainLoadsBeforeRemove( 
            /* [in] */ ldIStrainLoadItem *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIStrainLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIStrainLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIStrainLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIStrainLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsChanged )( 
            ldIStrainLoadsEvents * This,
            /* [in] */ ldIStrainLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsAdded )( 
            ldIStrainLoadsEvents * This,
            /* [in] */ ldIStrainLoadItem *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnStrainLoadsBeforeRemove )( 
            ldIStrainLoadsEvents * This,
            /* [in] */ ldIStrainLoadItem *load);
        
        END_INTERFACE
    } ldIStrainLoadsEventsVtbl;

    interface ldIStrainLoadsEvents
    {
        CONST_VTBL struct ldIStrainLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIStrainLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIStrainLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIStrainLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIStrainLoadsEvents_OnStrainLoadsChanged(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsChanged(This,load) ) 

#define ldIStrainLoadsEvents_OnStrainLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsAdded(This,load) ) 

#define ldIStrainLoadsEvents_OnStrainLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnStrainLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIStrainLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldIAxle_INTERFACE_DEFINED__
#define __ldIAxle_INTERFACE_DEFINED__

/* interface ldIAxle */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIAxle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A14A53DD-588E-4701-905D-8B981698D545")
    ldIAxle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Weight( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Weight( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Spacing( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Spacing( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIAxle **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIAxleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIAxle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIAxle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIAxle * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Weight )( 
            ldIAxle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Weight )( 
            ldIAxle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Spacing )( 
            ldIAxle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Spacing )( 
            ldIAxle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIAxle * This,
            /* [retval][out] */ ldIAxle **clone);
        
        END_INTERFACE
    } ldIAxleVtbl;

    interface ldIAxle
    {
        CONST_VTBL struct ldIAxleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIAxle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIAxle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIAxle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIAxle_get_Weight(This,pVal)	\
    ( (This)->lpVtbl -> get_Weight(This,pVal) ) 

#define ldIAxle_put_Weight(This,newVal)	\
    ( (This)->lpVtbl -> put_Weight(This,newVal) ) 

#define ldIAxle_get_Spacing(This,pVal)	\
    ( (This)->lpVtbl -> get_Spacing(This,pVal) ) 

#define ldIAxle_put_Spacing(This,newVal)	\
    ( (This)->lpVtbl -> put_Spacing(This,newVal) ) 

#define ldIAxle_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIAxle_INTERFACE_DEFINED__ */


#ifndef __ldIAxleEvents_INTERFACE_DEFINED__
#define __ldIAxleEvents_INTERFACE_DEFINED__

/* interface ldIAxleEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIAxleEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4C4FCC10-49BB-409e-BE31-1BCFAE9A2EA9")
    ldIAxleEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxleChanged( 
            /* [in] */ ldIAxle *me) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIAxleEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIAxleEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIAxleEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIAxleEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxleChanged )( 
            ldIAxleEvents * This,
            /* [in] */ ldIAxle *me);
        
        END_INTERFACE
    } ldIAxleEventsVtbl;

    interface ldIAxleEvents
    {
        CONST_VTBL struct ldIAxleEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIAxleEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIAxleEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIAxleEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIAxleEvents_OnAxleChanged(This,me)	\
    ( (This)->lpVtbl -> OnAxleChanged(This,me) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIAxleEvents_INTERFACE_DEFINED__ */


#ifndef __ldIEnumAxle_INTERFACE_DEFINED__
#define __ldIEnumAxle_INTERFACE_DEFINED__

/* interface ldIEnumAxle */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumAxle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B947B76C-F720-4408-B45E-7D2225A45BE1")
    ldIEnumAxle : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumAxle **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldIAxle **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumAxleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumAxle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumAxle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumAxle * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumAxle * This,
            /* [out] */ ldIEnumAxle **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumAxle * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldIAxle **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumAxle * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumAxle * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumAxleVtbl;

    interface ldIEnumAxle
    {
        CONST_VTBL struct ldIEnumAxleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumAxle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumAxle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumAxle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumAxle_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumAxle_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumAxle_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumAxle_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumAxle_INTERFACE_DEFINED__ */


#ifndef __ldIAxles_INTERFACE_DEFINED__
#define __ldIAxles_INTERFACE_DEFINED__

/* interface ldIAxles */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIAxles;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3202C18D-C33B-40e5-A706-A5E7A91EE8BE")
    ldIAxles : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ AxleIndexType position,
            /* [retval][out] */ ldIAxle **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ AxleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ldIAxle *__MIDL__ldIAxles0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ AxleIndexType relPosition,
            /* [in] */ ldIAxle *member) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ AxleIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reverse( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumAxle **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIAxles **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIAxlesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIAxles * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIAxles * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIAxles * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldIAxles * This,
            /* [in] */ AxleIndexType position,
            /* [retval][out] */ ldIAxle **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldIAxles * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldIAxles * This,
            /* [retval][out] */ AxleIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldIAxles * This,
            /* [in] */ ldIAxle *__MIDL__ldIAxles0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ldIAxles * This,
            /* [in] */ AxleIndexType relPosition,
            /* [in] */ ldIAxle *member);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            ldIAxles * This,
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *CopyTo )( 
            ldIAxles * This,
            /* [in] */ AxleIndexType fromPosition,
            /* [in] */ AxleIndexType toPosition);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ldIAxles * This,
            /* [in] */ AxleIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reverse )( 
            ldIAxles * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldIAxles * This,
            /* [retval][out] */ ldIEnumAxle **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIAxles * This,
            /* [retval][out] */ ldIAxles **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldIAxles * This);
        
        END_INTERFACE
    } ldIAxlesVtbl;

    interface ldIAxles
    {
        CONST_VTBL struct ldIAxlesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIAxles_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIAxles_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIAxles_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIAxles_get_Item(This,position,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,position,pVal) ) 

#define ldIAxles_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldIAxles_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldIAxles_Add(This,__MIDL__ldIAxles0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ldIAxles0000) ) 

#define ldIAxles_Insert(This,relPosition,member)	\
    ( (This)->lpVtbl -> Insert(This,relPosition,member) ) 

#define ldIAxles_MoveTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> MoveTo(This,fromPosition,toPosition) ) 

#define ldIAxles_CopyTo(This,fromPosition,toPosition)	\
    ( (This)->lpVtbl -> CopyTo(This,fromPosition,toPosition) ) 

#define ldIAxles_Remove(This,position)	\
    ( (This)->lpVtbl -> Remove(This,position) ) 

#define ldIAxles_Reverse(This)	\
    ( (This)->lpVtbl -> Reverse(This) ) 

#define ldIAxles_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldIAxles_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldIAxles_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIAxles_INTERFACE_DEFINED__ */


#ifndef __ldIAxlesEvents_INTERFACE_DEFINED__
#define __ldIAxlesEvents_INTERFACE_DEFINED__

/* interface ldIAxlesEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIAxlesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("59D31E9E-D8D6-49f5-897B-90499F15E6B7")
    ldIAxlesEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesChanged( 
            /* [in] */ ldIAxle *Axle) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesAdded( 
            /* [in] */ ldIAxle *Axle,
            /* [in] */ AxleIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesBeforeRemove( 
            /* [in] */ ldIAxle *Axle,
            /* [in] */ AxleIndexType position) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesMoveTo( 
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesCopyTo( 
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnAxlesReverse( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIAxlesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIAxlesEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIAxlesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIAxlesEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesChanged )( 
            ldIAxlesEvents * This,
            /* [in] */ ldIAxle *Axle);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesAdded )( 
            ldIAxlesEvents * This,
            /* [in] */ ldIAxle *Axle,
            /* [in] */ AxleIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesBeforeRemove )( 
            ldIAxlesEvents * This,
            /* [in] */ ldIAxle *Axle,
            /* [in] */ AxleIndexType position);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesMoveTo )( 
            ldIAxlesEvents * This,
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesCopyTo )( 
            ldIAxlesEvents * This,
            /* [in] */ AxleIndexType from,
            /* [in] */ AxleIndexType to);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnAxlesReverse )( 
            ldIAxlesEvents * This);
        
        END_INTERFACE
    } ldIAxlesEventsVtbl;

    interface ldIAxlesEvents
    {
        CONST_VTBL struct ldIAxlesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIAxlesEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIAxlesEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIAxlesEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIAxlesEvents_OnAxlesChanged(This,Axle)	\
    ( (This)->lpVtbl -> OnAxlesChanged(This,Axle) ) 

#define ldIAxlesEvents_OnAxlesAdded(This,Axle,position)	\
    ( (This)->lpVtbl -> OnAxlesAdded(This,Axle,position) ) 

#define ldIAxlesEvents_OnAxlesBeforeRemove(This,Axle,position)	\
    ( (This)->lpVtbl -> OnAxlesBeforeRemove(This,Axle,position) ) 

#define ldIAxlesEvents_OnAxlesMoveTo(This,from,to)	\
    ( (This)->lpVtbl -> OnAxlesMoveTo(This,from,to) ) 

#define ldIAxlesEvents_OnAxlesCopyTo(This,from,to)	\
    ( (This)->lpVtbl -> OnAxlesCopyTo(This,from,to) ) 

#define ldIAxlesEvents_OnAxlesReverse(This)	\
    ( (This)->lpVtbl -> OnAxlesReverse(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIAxlesEvents_INTERFACE_DEFINED__ */


#ifndef __ldIVehicularLoad_INTERFACE_DEFINED__
#define __ldIVehicularLoad_INTERFACE_DEFINED__

/* interface ldIVehicularLoad */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIVehicularLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27BF270B-9FA9-4946-A20A-C78C424FB18C")
    ldIVehicularLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Configuration( 
            /* [retval][out] */ ldVehicularLoadConfigurationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Configuration( 
            /* [in] */ ldVehicularLoadConfigurationType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_UseNotional( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_UseNotional( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Applicability( 
            /* [retval][out] */ ldLiveLoadApplicabilityType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Applicability( 
            /* [in] */ ldLiveLoadApplicabilityType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Axles( 
            /* [retval][out] */ ldIAxles **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Axles( 
            /* [in] */ ldIAxles *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariableAxle( 
            /* [retval][out] */ AxleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariableAxle( 
            /* [in] */ AxleIndexType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_VariableMaxSpacing( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_VariableMaxSpacing( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LaneLoad( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LaneLoad( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SidewalkLoad( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SidewalkLoad( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TruckFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TruckFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LaneFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LaneFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IMTruck( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IMTruck( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IMLane( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_IMLane( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIVehicularLoad **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIVehicularLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIVehicularLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIVehicularLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIVehicularLoad * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ldIVehicularLoad * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Configuration )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ ldVehicularLoadConfigurationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Configuration )( 
            ldIVehicularLoad * This,
            /* [in] */ ldVehicularLoadConfigurationType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UseNotional )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UseNotional )( 
            ldIVehicularLoad * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Applicability )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ ldLiveLoadApplicabilityType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Applicability )( 
            ldIVehicularLoad * This,
            /* [in] */ ldLiveLoadApplicabilityType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Axles )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ ldIAxles **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Axles )( 
            ldIVehicularLoad * This,
            /* [in] */ ldIAxles *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariableAxle )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ AxleIndexType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariableAxle )( 
            ldIVehicularLoad * This,
            /* [in] */ AxleIndexType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VariableMaxSpacing )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VariableMaxSpacing )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LaneLoad )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LaneLoad )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SidewalkLoad )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SidewalkLoad )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TruckFactor )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TruckFactor )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LaneFactor )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LaneFactor )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IMTruck )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IMTruck )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IMLane )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IMLane )( 
            ldIVehicularLoad * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIVehicularLoad * This,
            /* [retval][out] */ ldIVehicularLoad **clone);
        
        END_INTERFACE
    } ldIVehicularLoadVtbl;

    interface ldIVehicularLoad
    {
        CONST_VTBL struct ldIVehicularLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIVehicularLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIVehicularLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIVehicularLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIVehicularLoad_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ldIVehicularLoad_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ldIVehicularLoad_get_Configuration(This,pVal)	\
    ( (This)->lpVtbl -> get_Configuration(This,pVal) ) 

#define ldIVehicularLoad_put_Configuration(This,newVal)	\
    ( (This)->lpVtbl -> put_Configuration(This,newVal) ) 

#define ldIVehicularLoad_get_UseNotional(This,pVal)	\
    ( (This)->lpVtbl -> get_UseNotional(This,pVal) ) 

#define ldIVehicularLoad_put_UseNotional(This,newVal)	\
    ( (This)->lpVtbl -> put_UseNotional(This,newVal) ) 

#define ldIVehicularLoad_get_Applicability(This,pVal)	\
    ( (This)->lpVtbl -> get_Applicability(This,pVal) ) 

#define ldIVehicularLoad_put_Applicability(This,newVal)	\
    ( (This)->lpVtbl -> put_Applicability(This,newVal) ) 

#define ldIVehicularLoad_get_Axles(This,pVal)	\
    ( (This)->lpVtbl -> get_Axles(This,pVal) ) 

#define ldIVehicularLoad_putref_Axles(This,newVal)	\
    ( (This)->lpVtbl -> putref_Axles(This,newVal) ) 

#define ldIVehicularLoad_get_VariableAxle(This,pVal)	\
    ( (This)->lpVtbl -> get_VariableAxle(This,pVal) ) 

#define ldIVehicularLoad_put_VariableAxle(This,newVal)	\
    ( (This)->lpVtbl -> put_VariableAxle(This,newVal) ) 

#define ldIVehicularLoad_get_VariableMaxSpacing(This,pVal)	\
    ( (This)->lpVtbl -> get_VariableMaxSpacing(This,pVal) ) 

#define ldIVehicularLoad_put_VariableMaxSpacing(This,newVal)	\
    ( (This)->lpVtbl -> put_VariableMaxSpacing(This,newVal) ) 

#define ldIVehicularLoad_get_LaneLoad(This,pVal)	\
    ( (This)->lpVtbl -> get_LaneLoad(This,pVal) ) 

#define ldIVehicularLoad_put_LaneLoad(This,newVal)	\
    ( (This)->lpVtbl -> put_LaneLoad(This,newVal) ) 

#define ldIVehicularLoad_get_SidewalkLoad(This,pVal)	\
    ( (This)->lpVtbl -> get_SidewalkLoad(This,pVal) ) 

#define ldIVehicularLoad_put_SidewalkLoad(This,newVal)	\
    ( (This)->lpVtbl -> put_SidewalkLoad(This,newVal) ) 

#define ldIVehicularLoad_get_TruckFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_TruckFactor(This,pVal) ) 

#define ldIVehicularLoad_put_TruckFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_TruckFactor(This,newVal) ) 

#define ldIVehicularLoad_get_LaneFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_LaneFactor(This,pVal) ) 

#define ldIVehicularLoad_put_LaneFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_LaneFactor(This,newVal) ) 

#define ldIVehicularLoad_get_IMTruck(This,pVal)	\
    ( (This)->lpVtbl -> get_IMTruck(This,pVal) ) 

#define ldIVehicularLoad_put_IMTruck(This,newVal)	\
    ( (This)->lpVtbl -> put_IMTruck(This,newVal) ) 

#define ldIVehicularLoad_get_IMLane(This,pVal)	\
    ( (This)->lpVtbl -> get_IMLane(This,pVal) ) 

#define ldIVehicularLoad_put_IMLane(This,newVal)	\
    ( (This)->lpVtbl -> put_IMLane(This,newVal) ) 

#define ldIVehicularLoad_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIVehicularLoad_INTERFACE_DEFINED__ */


#ifndef __ldIVehicularLoadEvents_INTERFACE_DEFINED__
#define __ldIVehicularLoadEvents_INTERFACE_DEFINED__

/* interface ldIVehicularLoadEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIVehicularLoadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E8C23A9-A40F-475b-B241-C0064ADCD874")
    ldIVehicularLoadEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadChanged( 
            /* [in] */ ldIVehicularLoad *me,
            ldLoadingChangeType changed) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIVehicularLoadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIVehicularLoadEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIVehicularLoadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIVehicularLoadEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadChanged )( 
            ldIVehicularLoadEvents * This,
            /* [in] */ ldIVehicularLoad *me,
            ldLoadingChangeType changed);
        
        END_INTERFACE
    } ldIVehicularLoadEventsVtbl;

    interface ldIVehicularLoadEvents
    {
        CONST_VTBL struct ldIVehicularLoadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIVehicularLoadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIVehicularLoadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIVehicularLoadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIVehicularLoadEvents_OnVehicularLoadChanged(This,me,changed)	\
    ( (This)->lpVtbl -> OnVehicularLoadChanged(This,me,changed) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIVehicularLoadEvents_INTERFACE_DEFINED__ */


#ifndef __ldIEnumVehicularLoad_INTERFACE_DEFINED__
#define __ldIEnumVehicularLoad_INTERFACE_DEFINED__

/* interface ldIEnumVehicularLoad */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumVehicularLoad;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("130BE712-D57F-4329-9B8B-0E76EF6A6D66")
    ldIEnumVehicularLoad : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumVehicularLoad **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldIVehicularLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumVehicularLoadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumVehicularLoad * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumVehicularLoad * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumVehicularLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumVehicularLoad * This,
            /* [out] */ ldIEnumVehicularLoad **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumVehicularLoad * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldIVehicularLoad **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumVehicularLoad * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumVehicularLoad * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumVehicularLoadVtbl;

    interface ldIEnumVehicularLoad
    {
        CONST_VTBL struct ldIEnumVehicularLoadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumVehicularLoad_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumVehicularLoad_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumVehicularLoad_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumVehicularLoad_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumVehicularLoad_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumVehicularLoad_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumVehicularLoad_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumVehicularLoad_INTERFACE_DEFINED__ */


#ifndef __ldIVehicularLoads_INTERFACE_DEFINED__
#define __ldIVehicularLoads_INTERFACE_DEFINED__

/* interface ldIVehicularLoads */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldIVehicularLoads;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2C7CE61-BD50-48e5-A53A-49E280AA414E")
    ldIVehicularLoads : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VehicleIndexType index,
            /* [retval][out] */ ldIVehicularLoad **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ VehicleIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumVehicularLoad **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ VehicleIndexType index,
            /* [in] */ ldIVehicularLoad *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ldIVehicularLoad *__MIDL__ldIVehicularLoads0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VehicleIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldIVehicularLoads **__MIDL__ldIVehicularLoads0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIVehicularLoadsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIVehicularLoads * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIVehicularLoads * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIVehicularLoads * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldIVehicularLoads * This,
            /* [in] */ VehicleIndexType index,
            /* [retval][out] */ ldIVehicularLoad **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldIVehicularLoads * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldIVehicularLoads * This,
            /* [retval][out] */ VehicleIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldIVehicularLoads * This,
            /* [retval][out] */ ldIEnumVehicularLoad **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Insert )( 
            ldIVehicularLoads * This,
            /* [in] */ VehicleIndexType index,
            /* [in] */ ldIVehicularLoad *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldIVehicularLoads * This,
            /* [in] */ ldIVehicularLoad *__MIDL__ldIVehicularLoads0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ldIVehicularLoads * This,
            /* [in] */ VehicleIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIVehicularLoads * This,
            /* [retval][out] */ ldIVehicularLoads **__MIDL__ldIVehicularLoads0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldIVehicularLoads * This);
        
        END_INTERFACE
    } ldIVehicularLoadsVtbl;

    interface ldIVehicularLoads
    {
        CONST_VTBL struct ldIVehicularLoadsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIVehicularLoads_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIVehicularLoads_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIVehicularLoads_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIVehicularLoads_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldIVehicularLoads_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldIVehicularLoads_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldIVehicularLoads_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldIVehicularLoads_Insert(This,index,pVal)	\
    ( (This)->lpVtbl -> Insert(This,index,pVal) ) 

#define ldIVehicularLoads_Add(This,__MIDL__ldIVehicularLoads0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ldIVehicularLoads0000) ) 

#define ldIVehicularLoads_Remove(This,index)	\
    ( (This)->lpVtbl -> Remove(This,index) ) 

#define ldIVehicularLoads_Clone(This,__MIDL__ldIVehicularLoads0001)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__ldIVehicularLoads0001) ) 

#define ldIVehicularLoads_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIVehicularLoads_INTERFACE_DEFINED__ */


#ifndef __ldIVehicularLoadsEvents_INTERFACE_DEFINED__
#define __ldIVehicularLoadsEvents_INTERFACE_DEFINED__

/* interface ldIVehicularLoadsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldIVehicularLoadsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36EE5876-C9A7-404d-8EB1-4C5D7D72BB7F")
    ldIVehicularLoadsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsChanged( 
            /* [in] */ ldIVehicularLoad *load,
            ldLoadingChangeType changed) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsAdded( 
            /* [in] */ ldIVehicularLoad *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnVehicularLoadsBeforeRemove( 
            /* [in] */ ldIVehicularLoad *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIVehicularLoadsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIVehicularLoadsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIVehicularLoadsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIVehicularLoadsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsChanged )( 
            ldIVehicularLoadsEvents * This,
            /* [in] */ ldIVehicularLoad *load,
            ldLoadingChangeType changed);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsRenamed )( 
            ldIVehicularLoadsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsAdded )( 
            ldIVehicularLoadsEvents * This,
            /* [in] */ ldIVehicularLoad *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnVehicularLoadsBeforeRemove )( 
            ldIVehicularLoadsEvents * This,
            /* [in] */ ldIVehicularLoad *load);
        
        END_INTERFACE
    } ldIVehicularLoadsEventsVtbl;

    interface ldIVehicularLoadsEvents
    {
        CONST_VTBL struct ldIVehicularLoadsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIVehicularLoadsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIVehicularLoadsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIVehicularLoadsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIVehicularLoadsEvents_OnVehicularLoadsChanged(This,load,changed)	\
    ( (This)->lpVtbl -> OnVehicularLoadsChanged(This,load,changed) ) 

#define ldIVehicularLoadsEvents_OnVehicularLoadsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnVehicularLoadsRenamed(This,oldName,newName) ) 

#define ldIVehicularLoadsEvents_OnVehicularLoadsAdded(This,load)	\
    ( (This)->lpVtbl -> OnVehicularLoadsAdded(This,load) ) 

#define ldIVehicularLoadsEvents_OnVehicularLoadsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnVehicularLoadsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIVehicularLoadsEvents_INTERFACE_DEFINED__ */


#ifndef __ldILoadGroup_INTERFACE_DEFINED__
#define __ldILoadGroup_INTERFACE_DEFINED__

/* interface ldILoadGroup */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("167D825F-5AD5-459d-845A-9B7993B236F6")
    ldILoadGroup : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadGroup **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Transient( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Transient( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadGroup * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ldILoadGroup * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ldILoadGroup * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ldILoadGroup * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ldILoadGroup * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadGroup * This,
            /* [retval][out] */ ldILoadGroup **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transient )( 
            ldILoadGroup * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Transient )( 
            ldILoadGroup * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } ldILoadGroupVtbl;

    interface ldILoadGroup
    {
        CONST_VTBL struct ldILoadGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadGroup_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ldILoadGroup_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ldILoadGroup_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ldILoadGroup_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ldILoadGroup_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldILoadGroup_get_Transient(This,pVal)	\
    ( (This)->lpVtbl -> get_Transient(This,pVal) ) 

#define ldILoadGroup_put_Transient(This,newVal)	\
    ( (This)->lpVtbl -> put_Transient(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadGroup_INTERFACE_DEFINED__ */


#ifndef __ldILoadGroupEvents_INTERFACE_DEFINED__
#define __ldILoadGroupEvents_INTERFACE_DEFINED__

/* interface ldILoadGroupEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadGroupEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B461584-5AB1-410b-B2B0-3FA27A57396A")
    ldILoadGroupEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupChanged( 
            /* [in] */ ldILoadGroup *me,
            /* [in] */ ldLoadingChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadGroupEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadGroupEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadGroupEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadGroupEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupChanged )( 
            ldILoadGroupEvents * This,
            /* [in] */ ldILoadGroup *me,
            /* [in] */ ldLoadingChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupRenamed )( 
            ldILoadGroupEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ldILoadGroupEventsVtbl;

    interface ldILoadGroupEvents
    {
        CONST_VTBL struct ldILoadGroupEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadGroupEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadGroupEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadGroupEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadGroupEvents_OnLoadGroupChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadGroupChanged(This,me,type) ) 

#define ldILoadGroupEvents_OnLoadGroupRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadGroupRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadGroupEvents_INTERFACE_DEFINED__ */


#ifndef __ldIEnumLoadGroup_INTERFACE_DEFINED__
#define __ldIEnumLoadGroup_INTERFACE_DEFINED__

/* interface ldIEnumLoadGroup */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumLoadGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3E01D87F-8080-4b83-A656-F2A531B51061")
    ldIEnumLoadGroup : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumLoadGroup **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumLoadGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumLoadGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumLoadGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumLoadGroup * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumLoadGroup * This,
            /* [out] */ ldIEnumLoadGroup **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumLoadGroup * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumLoadGroup * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumLoadGroup * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumLoadGroupVtbl;

    interface ldIEnumLoadGroup
    {
        CONST_VTBL struct ldIEnumLoadGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumLoadGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumLoadGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumLoadGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumLoadGroup_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumLoadGroup_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumLoadGroup_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumLoadGroup_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumLoadGroup_INTERFACE_DEFINED__ */


#ifndef __ldILoadGroups_INTERFACE_DEFINED__
#define __ldILoadGroups_INTERFACE_DEFINED__

/* interface ldILoadGroups */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B952CBA6-84C4-4303-85F8-AF319D3B5A82")
    ldILoadGroups : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadGroup **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumLoadGroup **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadGroup **__MIDL__ldILoadGroups0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ldILoadGroup *__MIDL__ldILoadGroups0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadGroups **__MIDL__ldILoadGroups0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadGroups * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadGroups * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadGroups * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldILoadGroups * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadGroup **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldILoadGroups * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldILoadGroups * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldILoadGroups * This,
            /* [retval][out] */ ldIEnumLoadGroup **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldILoadGroups * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadGroup **__MIDL__ldILoadGroups0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldILoadGroups * This,
            /* [in] */ ldILoadGroup *__MIDL__ldILoadGroups0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ldILoadGroups * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldILoadGroups * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadGroups * This,
            /* [retval][out] */ ldILoadGroups **__MIDL__ldILoadGroups0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldILoadGroups * This);
        
        END_INTERFACE
    } ldILoadGroupsVtbl;

    interface ldILoadGroups
    {
        CONST_VTBL struct ldILoadGroupsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadGroups_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadGroups_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadGroups_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadGroups_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldILoadGroups_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldILoadGroups_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldILoadGroups_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldILoadGroups_Find(This,name,__MIDL__ldILoadGroups0000)	\
    ( (This)->lpVtbl -> Find(This,name,__MIDL__ldILoadGroups0000) ) 

#define ldILoadGroups_Add(This,__MIDL__ldILoadGroups0001)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ldILoadGroups0001) ) 

#define ldILoadGroups_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ldILoadGroups_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ldILoadGroups_Clone(This,__MIDL__ldILoadGroups0002)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__ldILoadGroups0002) ) 

#define ldILoadGroups_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadGroups_INTERFACE_DEFINED__ */


#ifndef __ldILoadGroupsEvents_INTERFACE_DEFINED__
#define __ldILoadGroupsEvents_INTERFACE_DEFINED__

/* interface ldILoadGroupsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadGroupsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D46C46B3-ECB0-4451-B8DF-29CBF26D53BF")
    ldILoadGroupsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsChanged( 
            /* [in] */ ldILoadGroup *load,
            /* [in] */ ldLoadingChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsAdded( 
            /* [in] */ ldILoadGroup *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadGroupsBeforeRemove( 
            /* [in] */ ldILoadGroup *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadGroupsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadGroupsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadGroupsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadGroupsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsChanged )( 
            ldILoadGroupsEvents * This,
            /* [in] */ ldILoadGroup *load,
            /* [in] */ ldLoadingChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsRenamed )( 
            ldILoadGroupsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsAdded )( 
            ldILoadGroupsEvents * This,
            /* [in] */ ldILoadGroup *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadGroupsBeforeRemove )( 
            ldILoadGroupsEvents * This,
            /* [in] */ ldILoadGroup *load);
        
        END_INTERFACE
    } ldILoadGroupsEventsVtbl;

    interface ldILoadGroupsEvents
    {
        CONST_VTBL struct ldILoadGroupsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadGroupsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadGroupsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadGroupsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadGroupsEvents_OnLoadGroupsChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadGroupsChanged(This,load,change) ) 

#define ldILoadGroupsEvents_OnLoadGroupsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadGroupsRenamed(This,oldName,newName) ) 

#define ldILoadGroupsEvents_OnLoadGroupsAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadGroupsAdded(This,load) ) 

#define ldILoadGroupsEvents_OnLoadGroupsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadGroupsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadGroupsEvents_INTERFACE_DEFINED__ */


#ifndef __ldILoadCase_INTERFACE_DEFINED__
#define __ldILoadCase_INTERFACE_DEFINED__

/* interface ldILoadCase */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadCase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FC9429CE-F553-4fbb-9436-32027A50294C")
    ldILoadCase : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemData( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ItemData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLoadGroup( 
            /* [in] */ BSTR loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadGroup( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadGroup( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadGroup( 
            /* [in] */ BSTR loadGroupName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadGroupByIndex( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadCase **clone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadGroupCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCase * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ldILoadCase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ldILoadCase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ldILoadCase * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ldILoadCase * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemData )( 
            ldILoadCase * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemData )( 
            ldILoadCase * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldILoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLoadGroup )( 
            ldILoadCase * This,
            /* [in] */ BSTR loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadGroup )( 
            ldILoadCase * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadGroup )( 
            ldILoadCase * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadGroup )( 
            ldILoadCase * This,
            /* [in] */ BSTR loadGroupName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadGroupByIndex )( 
            ldILoadCase * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadCase * This,
            /* [retval][out] */ ldILoadCase **clone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadGroupCount )( 
            ldILoadCase * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        END_INTERFACE
    } ldILoadCaseVtbl;

    interface ldILoadCase
    {
        CONST_VTBL struct ldILoadCaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCase_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ldILoadCase_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ldILoadCase_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ldILoadCase_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ldILoadCase_get_ItemData(This,pVal)	\
    ( (This)->lpVtbl -> get_ItemData(This,pVal) ) 

#define ldILoadCase_put_ItemData(This,newVal)	\
    ( (This)->lpVtbl -> put_ItemData(This,newVal) ) 

#define ldILoadCase_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldILoadCase_AddLoadGroup(This,loadGroupName)	\
    ( (This)->lpVtbl -> AddLoadGroup(This,loadGroupName) ) 

#define ldILoadCase_GetLoadGroup(This,index,loadGroupName)	\
    ( (This)->lpVtbl -> GetLoadGroup(This,index,loadGroupName) ) 

#define ldILoadCase_SetLoadGroup(This,index,newName)	\
    ( (This)->lpVtbl -> SetLoadGroup(This,index,newName) ) 

#define ldILoadCase_RemoveLoadGroup(This,loadGroupName)	\
    ( (This)->lpVtbl -> RemoveLoadGroup(This,loadGroupName) ) 

#define ldILoadCase_RemoveLoadGroupByIndex(This,index)	\
    ( (This)->lpVtbl -> RemoveLoadGroupByIndex(This,index) ) 

#define ldILoadCase_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldILoadCase_get_LoadGroupCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadGroupCount(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCase_INTERFACE_DEFINED__ */


#ifndef __ldILoadCaseEvents_INTERFACE_DEFINED__
#define __ldILoadCaseEvents_INTERFACE_DEFINED__

/* interface ldILoadCaseEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadCaseEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2DCA8D9-CA41-4a04-B7F9-4825A4940491")
    ldILoadCaseEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCaseChanged( 
            /* [in] */ ldILoadCase *me,
            /* [in] */ ldLoadingChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCaseRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCaseEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCaseEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCaseEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCaseEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCaseChanged )( 
            ldILoadCaseEvents * This,
            /* [in] */ ldILoadCase *me,
            /* [in] */ ldLoadingChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCaseRenamed )( 
            ldILoadCaseEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ldILoadCaseEventsVtbl;

    interface ldILoadCaseEvents
    {
        CONST_VTBL struct ldILoadCaseEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCaseEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCaseEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCaseEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCaseEvents_OnLoadCaseChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadCaseChanged(This,me,type) ) 

#define ldILoadCaseEvents_OnLoadCaseRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCaseRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCaseEvents_INTERFACE_DEFINED__ */


#ifndef __ldIEnumLoadCase_INTERFACE_DEFINED__
#define __ldIEnumLoadCase_INTERFACE_DEFINED__

/* interface ldIEnumLoadCase */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumLoadCase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("329AF1B2-38E0-4d3b-BC44-895D62132E08")
    ldIEnumLoadCase : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumLoadCase **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadCase **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumLoadCaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumLoadCase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumLoadCase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumLoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumLoadCase * This,
            /* [out] */ ldIEnumLoadCase **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumLoadCase * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadCase **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumLoadCase * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumLoadCase * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumLoadCaseVtbl;

    interface ldIEnumLoadCase
    {
        CONST_VTBL struct ldIEnumLoadCaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumLoadCase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumLoadCase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumLoadCase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumLoadCase_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumLoadCase_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumLoadCase_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumLoadCase_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumLoadCase_INTERFACE_DEFINED__ */


#ifndef __ldILoadCases_INTERFACE_DEFINED__
#define __ldILoadCases_INTERFACE_DEFINED__

/* interface ldILoadCases */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadCases;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("120C2E56-3AC8-4428-965C-22E68524FFCA")
    ldILoadCases : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadCase **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumLoadCase **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadCase **loadCase) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ldILoadCase *loadCase) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadCases **clone) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCasesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCases * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCases * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCases * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldILoadCases * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadCase **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldILoadCases * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldILoadCases * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldILoadCases * This,
            /* [retval][out] */ ldIEnumLoadCase **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldILoadCases * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadCase **loadCase);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldILoadCases * This,
            /* [in] */ ldILoadCase *loadCase);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ldILoadCases * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldILoadCases * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadCases * This,
            /* [retval][out] */ ldILoadCases **clone);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldILoadCases * This);
        
        END_INTERFACE
    } ldILoadCasesVtbl;

    interface ldILoadCases
    {
        CONST_VTBL struct ldILoadCasesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCases_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCases_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCases_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCases_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldILoadCases_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldILoadCases_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldILoadCases_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldILoadCases_Find(This,name,loadCase)	\
    ( (This)->lpVtbl -> Find(This,name,loadCase) ) 

#define ldILoadCases_Add(This,loadCase)	\
    ( (This)->lpVtbl -> Add(This,loadCase) ) 

#define ldILoadCases_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ldILoadCases_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ldILoadCases_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#define ldILoadCases_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCases_INTERFACE_DEFINED__ */


#ifndef __ldILoadCasesEvents_INTERFACE_DEFINED__
#define __ldILoadCasesEvents_INTERFACE_DEFINED__

/* interface ldILoadCasesEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadCasesEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A07D1640-37BD-4095-B814-C736E34E00FD")
    ldILoadCasesEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesChanged( 
            /* [in] */ ldILoadCase *load,
            /* [in] */ ldLoadingChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesAdded( 
            /* [in] */ ldILoadCase *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCasesBeforeRemove( 
            /* [in] */ ldILoadCase *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCasesEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCasesEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCasesEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCasesEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesChanged )( 
            ldILoadCasesEvents * This,
            /* [in] */ ldILoadCase *load,
            /* [in] */ ldLoadingChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesRenamed )( 
            ldILoadCasesEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesAdded )( 
            ldILoadCasesEvents * This,
            /* [in] */ ldILoadCase *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCasesBeforeRemove )( 
            ldILoadCasesEvents * This,
            /* [in] */ ldILoadCase *load);
        
        END_INTERFACE
    } ldILoadCasesEventsVtbl;

    interface ldILoadCasesEvents
    {
        CONST_VTBL struct ldILoadCasesEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCasesEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCasesEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCasesEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCasesEvents_OnLoadCasesChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadCasesChanged(This,load,change) ) 

#define ldILoadCasesEvents_OnLoadCasesRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCasesRenamed(This,oldName,newName) ) 

#define ldILoadCasesEvents_OnLoadCasesAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadCasesAdded(This,load) ) 

#define ldILoadCasesEvents_OnLoadCasesBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadCasesBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCasesEvents_INTERFACE_DEFINED__ */


#ifndef __ldILoadCombination_INTERFACE_DEFINED__
#define __ldILoadCombination_INTERFACE_DEFINED__

/* interface ldILoadCombination */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadCombination;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E129557-9D47-4246-BF2A-C2E963D2B676")
    ldILoadCombination : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadModel( 
            /* [retval][out] */ ldLiveLoadModelType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadModel( 
            /* [in] */ ldLiveLoadModelType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LiveLoadFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LiveLoadFactor( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCaseFactorCount( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetLoadCaseFactor( 
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddLoadCaseFactor( 
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetLoadCaseFactor( 
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveLoadCaseFactor( 
            /* [in] */ CollectionIndexType index) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadCombination **lone) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ItemData( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ItemData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_LoadCombinationType( 
            /* [retval][out] */ ldLoadCombinationType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_LoadCombinationType( 
            /* [in] */ ldLoadCombinationType newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCombinationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCombination * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCombination * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCombination * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            ldILoadCombination * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            ldILoadCombination * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ldILoadCombination * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ldILoadCombination * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadModel )( 
            ldILoadCombination * This,
            /* [retval][out] */ ldLiveLoadModelType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadModel )( 
            ldILoadCombination * This,
            /* [in] */ ldLiveLoadModelType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LiveLoadFactor )( 
            ldILoadCombination * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LiveLoadFactor )( 
            ldILoadCombination * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCaseFactorCount )( 
            ldILoadCombination * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLoadCaseFactor )( 
            ldILoadCombination * This,
            /* [in] */ CollectionIndexType index,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddLoadCaseFactor )( 
            ldILoadCombination * This,
            /* [in] */ BSTR loadCaseName,
            /* [in] */ Float64 minFactor,
            /* [in] */ Float64 maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLoadCaseFactor )( 
            ldILoadCombination * This,
            /* [in] */ CollectionIndexType index,
            /* [out] */ BSTR *loadCaseName,
            /* [out] */ Float64 *minFactor,
            /* [out] */ Float64 *maxFactor);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldILoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveLoadCaseFactor )( 
            ldILoadCombination * This,
            /* [in] */ CollectionIndexType index);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadCombination * This,
            /* [retval][out] */ ldILoadCombination **lone);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ItemData )( 
            ldILoadCombination * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ItemData )( 
            ldILoadCombination * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LoadCombinationType )( 
            ldILoadCombination * This,
            /* [retval][out] */ ldLoadCombinationType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LoadCombinationType )( 
            ldILoadCombination * This,
            /* [in] */ ldLoadCombinationType newVal);
        
        END_INTERFACE
    } ldILoadCombinationVtbl;

    interface ldILoadCombination
    {
        CONST_VTBL struct ldILoadCombinationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCombination_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCombination_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCombination_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCombination_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define ldILoadCombination_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#define ldILoadCombination_get_Description(This,pVal)	\
    ( (This)->lpVtbl -> get_Description(This,pVal) ) 

#define ldILoadCombination_put_Description(This,newVal)	\
    ( (This)->lpVtbl -> put_Description(This,newVal) ) 

#define ldILoadCombination_get_LiveLoadModel(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadModel(This,pVal) ) 

#define ldILoadCombination_put_LiveLoadModel(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadModel(This,newVal) ) 

#define ldILoadCombination_get_LiveLoadFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_LiveLoadFactor(This,pVal) ) 

#define ldILoadCombination_put_LiveLoadFactor(This,newVal)	\
    ( (This)->lpVtbl -> put_LiveLoadFactor(This,newVal) ) 

#define ldILoadCombination_get_LoadCaseFactorCount(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCaseFactorCount(This,pVal) ) 

#define ldILoadCombination_SetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> SetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor) ) 

#define ldILoadCombination_AddLoadCaseFactor(This,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> AddLoadCaseFactor(This,loadCaseName,minFactor,maxFactor) ) 

#define ldILoadCombination_GetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor)	\
    ( (This)->lpVtbl -> GetLoadCaseFactor(This,index,loadCaseName,minFactor,maxFactor) ) 

#define ldILoadCombination_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define ldILoadCombination_RemoveLoadCaseFactor(This,index)	\
    ( (This)->lpVtbl -> RemoveLoadCaseFactor(This,index) ) 

#define ldILoadCombination_Clone(This,lone)	\
    ( (This)->lpVtbl -> Clone(This,lone) ) 

#define ldILoadCombination_get_ItemData(This,pVal)	\
    ( (This)->lpVtbl -> get_ItemData(This,pVal) ) 

#define ldILoadCombination_put_ItemData(This,newVal)	\
    ( (This)->lpVtbl -> put_ItemData(This,newVal) ) 

#define ldILoadCombination_get_LoadCombinationType(This,pVal)	\
    ( (This)->lpVtbl -> get_LoadCombinationType(This,pVal) ) 

#define ldILoadCombination_put_LoadCombinationType(This,newVal)	\
    ( (This)->lpVtbl -> put_LoadCombinationType(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCombination_INTERFACE_DEFINED__ */


#ifndef __ldILoadCombinationEvents_INTERFACE_DEFINED__
#define __ldILoadCombinationEvents_INTERFACE_DEFINED__

/* interface ldILoadCombinationEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadCombinationEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8427522-7A09-40fb-8CBD-18A6A3573418")
    ldILoadCombinationEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationChanged( 
            /* [in] */ ldILoadCombination *me,
            /* [in] */ ldLoadingChangeType type) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCombinationEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCombinationEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCombinationEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCombinationEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationChanged )( 
            ldILoadCombinationEvents * This,
            /* [in] */ ldILoadCombination *me,
            /* [in] */ ldLoadingChangeType type);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationRenamed )( 
            ldILoadCombinationEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        END_INTERFACE
    } ldILoadCombinationEventsVtbl;

    interface ldILoadCombinationEvents
    {
        CONST_VTBL struct ldILoadCombinationEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCombinationEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCombinationEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCombinationEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCombinationEvents_OnLoadCombinationChanged(This,me,type)	\
    ( (This)->lpVtbl -> OnLoadCombinationChanged(This,me,type) ) 

#define ldILoadCombinationEvents_OnLoadCombinationRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCombinationRenamed(This,oldName,newName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCombinationEvents_INTERFACE_DEFINED__ */


#ifndef __ldIEnumLoadCombination_INTERFACE_DEFINED__
#define __ldIEnumLoadCombination_INTERFACE_DEFINED__

/* interface ldIEnumLoadCombination */
/* [unique][restricted][hidden][nonextensible][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ldIEnumLoadCombination;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1E07C7C3-8ABB-4338-BEA7-456884792E07")
    ldIEnumLoadCombination : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ ldIEnumLoadCombination **ppenum) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadCombination **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldIEnumLoadCombinationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldIEnumLoadCombination * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldIEnumLoadCombination * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldIEnumLoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldIEnumLoadCombination * This,
            /* [out] */ ldIEnumLoadCombination **ppenum);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            ldIEnumLoadCombination * This,
            /* [in] */ ULONG celt,
            /* [out] */ ldILoadCombination **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            ldIEnumLoadCombination * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            ldIEnumLoadCombination * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } ldIEnumLoadCombinationVtbl;

    interface ldIEnumLoadCombination
    {
        CONST_VTBL struct ldIEnumLoadCombinationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldIEnumLoadCombination_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldIEnumLoadCombination_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldIEnumLoadCombination_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldIEnumLoadCombination_Clone(This,ppenum)	\
    ( (This)->lpVtbl -> Clone(This,ppenum) ) 

#define ldIEnumLoadCombination_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define ldIEnumLoadCombination_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define ldIEnumLoadCombination_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldIEnumLoadCombination_INTERFACE_DEFINED__ */


#ifndef __ldILoadCombinations_INTERFACE_DEFINED__
#define __ldILoadCombinations_INTERFACE_DEFINED__

/* interface ldILoadCombinations */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ldILoadCombinations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC9E987A-69F8-4f96-A825-F7583A491113")
    ldILoadCombinations : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadCombination **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__EnumElements( 
            /* [retval][out] */ ldIEnumLoadCombination **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadCombination **__MIDL__ldILoadCombinations0000) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ ldILoadCombination *__MIDL__ldILoadCombinations0001) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByName( 
            /* [in] */ BSTR name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveByIndex( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ ldILoadCombinations **__MIDL__ldILoadCombinations0002) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCombinationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCombinations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCombinations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCombinations * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ldILoadCombinations * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ ldILoadCombination **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ldILoadCombinations * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ldILoadCombinations * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumElements )( 
            ldILoadCombinations * This,
            /* [retval][out] */ ldIEnumLoadCombination **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Find )( 
            ldILoadCombinations * This,
            /* [in] */ BSTR name,
            /* [retval][out] */ ldILoadCombination **__MIDL__ldILoadCombinations0000);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            ldILoadCombinations * This,
            /* [in] */ ldILoadCombination *__MIDL__ldILoadCombinations0001);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByName )( 
            ldILoadCombinations * This,
            /* [in] */ BSTR name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveByIndex )( 
            ldILoadCombinations * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ BSTR *name);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ldILoadCombinations * This,
            /* [retval][out] */ ldILoadCombinations **__MIDL__ldILoadCombinations0002);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            ldILoadCombinations * This);
        
        END_INTERFACE
    } ldILoadCombinationsVtbl;

    interface ldILoadCombinations
    {
        CONST_VTBL struct ldILoadCombinationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCombinations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCombinations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCombinations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCombinations_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define ldILoadCombinations_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define ldILoadCombinations_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ldILoadCombinations_get__EnumElements(This,pVal)	\
    ( (This)->lpVtbl -> get__EnumElements(This,pVal) ) 

#define ldILoadCombinations_Find(This,name,__MIDL__ldILoadCombinations0000)	\
    ( (This)->lpVtbl -> Find(This,name,__MIDL__ldILoadCombinations0000) ) 

#define ldILoadCombinations_Add(This,__MIDL__ldILoadCombinations0001)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__ldILoadCombinations0001) ) 

#define ldILoadCombinations_RemoveByName(This,name)	\
    ( (This)->lpVtbl -> RemoveByName(This,name) ) 

#define ldILoadCombinations_RemoveByIndex(This,index,name)	\
    ( (This)->lpVtbl -> RemoveByIndex(This,index,name) ) 

#define ldILoadCombinations_Clone(This,__MIDL__ldILoadCombinations0002)	\
    ( (This)->lpVtbl -> Clone(This,__MIDL__ldILoadCombinations0002) ) 

#define ldILoadCombinations_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCombinations_INTERFACE_DEFINED__ */


#ifndef __ldILoadCombinationsEvents_INTERFACE_DEFINED__
#define __ldILoadCombinationsEvents_INTERFACE_DEFINED__

/* interface ldILoadCombinationsEvents */
/* [helpstring][helpcontext][unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_ldILoadCombinationsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC9529DC-0265-4c9e-B3F8-DADBC0C0BAEA")
    ldILoadCombinationsEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsChanged( 
            /* [in] */ ldILoadCombination *load,
            /* [in] */ ldLoadingChangeType change) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsRenamed( 
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsAdded( 
            /* [in] */ ldILoadCombination *load) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE OnLoadCombinationsBeforeRemove( 
            /* [in] */ ldILoadCombination *load) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ldILoadCombinationsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ldILoadCombinationsEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ldILoadCombinationsEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ldILoadCombinationsEvents * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsChanged )( 
            ldILoadCombinationsEvents * This,
            /* [in] */ ldILoadCombination *load,
            /* [in] */ ldLoadingChangeType change);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsRenamed )( 
            ldILoadCombinationsEvents * This,
            /* [in] */ BSTR oldName,
            /* [in] */ BSTR newName);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsAdded )( 
            ldILoadCombinationsEvents * This,
            /* [in] */ ldILoadCombination *load);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnLoadCombinationsBeforeRemove )( 
            ldILoadCombinationsEvents * This,
            /* [in] */ ldILoadCombination *load);
        
        END_INTERFACE
    } ldILoadCombinationsEventsVtbl;

    interface ldILoadCombinationsEvents
    {
        CONST_VTBL struct ldILoadCombinationsEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ldILoadCombinationsEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ldILoadCombinationsEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ldILoadCombinationsEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ldILoadCombinationsEvents_OnLoadCombinationsChanged(This,load,change)	\
    ( (This)->lpVtbl -> OnLoadCombinationsChanged(This,load,change) ) 

#define ldILoadCombinationsEvents_OnLoadCombinationsRenamed(This,oldName,newName)	\
    ( (This)->lpVtbl -> OnLoadCombinationsRenamed(This,oldName,newName) ) 

#define ldILoadCombinationsEvents_OnLoadCombinationsAdded(This,load)	\
    ( (This)->lpVtbl -> OnLoadCombinationsAdded(This,load) ) 

#define ldILoadCombinationsEvents_OnLoadCombinationsBeforeRemove(This,load)	\
    ( (This)->lpVtbl -> OnLoadCombinationsBeforeRemove(This,load) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ldILoadCombinationsEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ldPointLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("EEA0ACB5-8975-4a22-A767-3E99B403927C")
ldPointLoad;
#endif

EXTERN_C const CLSID CLSID_ldPointLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("CFEF06F9-4670-46f1-8886-6A240F368CAB")
ldPointLoadItem;
#endif

EXTERN_C const CLSID CLSID_ldPointLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("5C044453-8A7B-4bd9-B6D8-071717C2CF30")
ldPointLoads;
#endif

EXTERN_C const CLSID CLSID_ldDistributedLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("3D861436-D4EE-48d6-919B-2C9092C84437")
ldDistributedLoad;
#endif

EXTERN_C const CLSID CLSID_ldDistributedLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("728C9541-A81D-4021-9021-E56159407B39")
ldDistributedLoadItem;
#endif

EXTERN_C const CLSID CLSID_ldDistributedLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("37F5CCA8-1487-46ee-9799-B6F19667992C")
ldDistributedLoads;
#endif

EXTERN_C const CLSID CLSID_ldSettlementLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("D789E133-AD3A-4716-A8FB-2CE053D16F54")
ldSettlementLoad;
#endif

EXTERN_C const CLSID CLSID_ldSettlementLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("E45903B2-349C-4400-84F1-5F57BD63B84B")
ldSettlementLoadItem;
#endif

EXTERN_C const CLSID CLSID_ldSettlementLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("7AA2979B-5D9B-43f6-86F0-D3E2432C0460")
ldSettlementLoads;
#endif

EXTERN_C const CLSID CLSID_ldTemperatureLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("B4D529B3-8751-4e31-9374-EE536BC4E181")
ldTemperatureLoad;
#endif

EXTERN_C const CLSID CLSID_ldTemperatureLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("E29B1273-A987-4ca9-8E22-525F679AC2BC")
ldTemperatureLoadItem;
#endif

EXTERN_C const CLSID CLSID_ldTemperatureLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("F7416351-EA9D-4e11-AACE-52A5ADA81166")
ldTemperatureLoads;
#endif

EXTERN_C const CLSID CLSID_ldStrainLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("D492704F-167D-4ef6-A42D-E71A00202D55")
ldStrainLoad;
#endif

EXTERN_C const CLSID CLSID_ldStrainLoadItem;

#ifdef __cplusplus

class DECLSPEC_UUID("C91BF36A-2CE9-450c-A6CC-186DE33D1EF6")
ldStrainLoadItem;
#endif

EXTERN_C const CLSID CLSID_ldStrainLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("E94C40B2-A06F-425f-86BD-0614C7949A40")
ldStrainLoads;
#endif

EXTERN_C const CLSID CLSID_ldAxle;

#ifdef __cplusplus

class DECLSPEC_UUID("6C8C9861-27F5-4453-8B5C-3D64BF6CA67E")
ldAxle;
#endif

EXTERN_C const CLSID CLSID_ldAxles;

#ifdef __cplusplus

class DECLSPEC_UUID("CB15EE10-4EE5-4c45-9DFE-4CE55278660C")
ldAxles;
#endif

EXTERN_C const CLSID CLSID_ldVehicularLoad;

#ifdef __cplusplus

class DECLSPEC_UUID("3BCDD419-7FAB-4fbf-9C49-BBFC2DCA7560")
ldVehicularLoad;
#endif

EXTERN_C const CLSID CLSID_ldVehicularLoads;

#ifdef __cplusplus

class DECLSPEC_UUID("DA308252-6092-4249-A15F-29145E216DDA")
ldVehicularLoads;
#endif

EXTERN_C const CLSID CLSID_ldLoadGroup;

#ifdef __cplusplus

class DECLSPEC_UUID("0531B51D-4A03-4adf-A0F5-F03AB8A7B319")
ldLoadGroup;
#endif

EXTERN_C const CLSID CLSID_ldLoadGroups;

#ifdef __cplusplus

class DECLSPEC_UUID("7A25B5EA-2193-4693-9773-4FF6BB87542C")
ldLoadGroups;
#endif

EXTERN_C const CLSID CLSID_ldLoadCase;

#ifdef __cplusplus

class DECLSPEC_UUID("EBCC806B-3E7C-4fe9-B4BA-E35C7A4B9D37")
ldLoadCase;
#endif

EXTERN_C const CLSID CLSID_ldLoadCases;

#ifdef __cplusplus

class DECLSPEC_UUID("A7B27015-3520-4599-862D-5F7B7BB9E951")
ldLoadCases;
#endif

EXTERN_C const CLSID CLSID_ldLoadCombination;

#ifdef __cplusplus

class DECLSPEC_UUID("FE736496-80C1-40a2-8E08-37D250580692")
ldLoadCombination;
#endif

EXTERN_C const CLSID CLSID_ldLoadCombinations;

#ifdef __cplusplus

class DECLSPEC_UUID("71218489-4944-4304-AAEF-B97361A750F1")
ldLoadCombinations;
#endif
#endif /* __WBFLLoading_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


