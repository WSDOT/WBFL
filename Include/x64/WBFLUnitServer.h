

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:24:47 2017
 */
/* Compiler settings for ..\Include\WbflUnitServer.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WBFLUnitServer_h__
#define __WBFLUnitServer_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDisplayUnitFormatter_FWD_DEFINED__
#define __IDisplayUnitFormatter_FWD_DEFINED__
typedef interface IDisplayUnitFormatter IDisplayUnitFormatter;

#endif 	/* __IDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __IAnnotatedDisplayUnitFormatter_FWD_DEFINED__
#define __IAnnotatedDisplayUnitFormatter_FWD_DEFINED__
typedef interface IAnnotatedDisplayUnitFormatter IAnnotatedDisplayUnitFormatter;

#endif 	/* __IAnnotatedDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __IUnits_FWD_DEFINED__
#define __IUnits_FWD_DEFINED__
typedef interface IUnits IUnits;

#endif 	/* __IUnits_FWD_DEFINED__ */


#ifndef __IUnitServer_FWD_DEFINED__
#define __IUnitServer_FWD_DEFINED__
typedef interface IUnitServer IUnitServer;

#endif 	/* __IUnitServer_FWD_DEFINED__ */


#ifndef __IUnitConvert_FWD_DEFINED__
#define __IUnitConvert_FWD_DEFINED__
typedef interface IUnitConvert IUnitConvert;

#endif 	/* __IUnitConvert_FWD_DEFINED__ */


#ifndef __IUnitConvert2_FWD_DEFINED__
#define __IUnitConvert2_FWD_DEFINED__
typedef interface IUnitConvert2 IUnitConvert2;

#endif 	/* __IUnitConvert2_FWD_DEFINED__ */


#ifndef __IUnitType_FWD_DEFINED__
#define __IUnitType_FWD_DEFINED__
typedef interface IUnitType IUnitType;

#endif 	/* __IUnitType_FWD_DEFINED__ */


#ifndef __IEnumUnitTypes_FWD_DEFINED__
#define __IEnumUnitTypes_FWD_DEFINED__
typedef interface IEnumUnitTypes IEnumUnitTypes;

#endif 	/* __IEnumUnitTypes_FWD_DEFINED__ */


#ifndef __IUnitTypes_FWD_DEFINED__
#define __IUnitTypes_FWD_DEFINED__
typedef interface IUnitTypes IUnitTypes;

#endif 	/* __IUnitTypes_FWD_DEFINED__ */


#ifndef __IUnit_FWD_DEFINED__
#define __IUnit_FWD_DEFINED__
typedef interface IUnit IUnit;

#endif 	/* __IUnit_FWD_DEFINED__ */


#ifndef __IEnumUnits_FWD_DEFINED__
#define __IEnumUnits_FWD_DEFINED__
typedef interface IEnumUnits IEnumUnits;

#endif 	/* __IEnumUnits_FWD_DEFINED__ */


#ifndef __IDisplayUnit_FWD_DEFINED__
#define __IDisplayUnit_FWD_DEFINED__
typedef interface IDisplayUnit IDisplayUnit;

#endif 	/* __IDisplayUnit_FWD_DEFINED__ */


#ifndef __IEnumDisplayUnits_FWD_DEFINED__
#define __IEnumDisplayUnits_FWD_DEFINED__
typedef interface IEnumDisplayUnits IEnumDisplayUnits;

#endif 	/* __IEnumDisplayUnits_FWD_DEFINED__ */


#ifndef __IDisplayUnitGroup_FWD_DEFINED__
#define __IDisplayUnitGroup_FWD_DEFINED__
typedef interface IDisplayUnitGroup IDisplayUnitGroup;

#endif 	/* __IDisplayUnitGroup_FWD_DEFINED__ */


#ifndef __IEnumDisplayUnitGroups_FWD_DEFINED__
#define __IEnumDisplayUnitGroups_FWD_DEFINED__
typedef interface IEnumDisplayUnitGroups IEnumDisplayUnitGroups;

#endif 	/* __IEnumDisplayUnitGroups_FWD_DEFINED__ */


#ifndef __IDisplayUnitMgr_FWD_DEFINED__
#define __IDisplayUnitMgr_FWD_DEFINED__
typedef interface IDisplayUnitMgr IDisplayUnitMgr;

#endif 	/* __IDisplayUnitMgr_FWD_DEFINED__ */


#ifndef __IUnitModeController_FWD_DEFINED__
#define __IUnitModeController_FWD_DEFINED__
typedef interface IUnitModeController IUnitModeController;

#endif 	/* __IUnitModeController_FWD_DEFINED__ */


#ifndef __IUnitSystem_FWD_DEFINED__
#define __IUnitSystem_FWD_DEFINED__
typedef interface IUnitSystem IUnitSystem;

#endif 	/* __IUnitSystem_FWD_DEFINED__ */


#ifndef __IDisplayUnitMgr2_FWD_DEFINED__
#define __IDisplayUnitMgr2_FWD_DEFINED__
typedef interface IDisplayUnitMgr2 IDisplayUnitMgr2;

#endif 	/* __IDisplayUnitMgr2_FWD_DEFINED__ */


#ifndef __IAppUnitSystem_FWD_DEFINED__
#define __IAppUnitSystem_FWD_DEFINED__
typedef interface IAppUnitSystem IAppUnitSystem;

#endif 	/* __IAppUnitSystem_FWD_DEFINED__ */


#ifndef __IDocUnitSystem_FWD_DEFINED__
#define __IDocUnitSystem_FWD_DEFINED__
typedef interface IDocUnitSystem IDocUnitSystem;

#endif 	/* __IDocUnitSystem_FWD_DEFINED__ */


#ifndef __ISupportUnitServer_FWD_DEFINED__
#define __ISupportUnitServer_FWD_DEFINED__
typedef interface ISupportUnitServer ISupportUnitServer;

#endif 	/* __ISupportUnitServer_FWD_DEFINED__ */


#ifndef __ISupportUnitSystem_FWD_DEFINED__
#define __ISupportUnitSystem_FWD_DEFINED__
typedef interface ISupportUnitSystem ISupportUnitSystem;

#endif 	/* __ISupportUnitSystem_FWD_DEFINED__ */


#ifndef __ISupportDisplayUnits_FWD_DEFINED__
#define __ISupportDisplayUnits_FWD_DEFINED__
typedef interface ISupportDisplayUnits ISupportDisplayUnits;

#endif 	/* __ISupportDisplayUnits_FWD_DEFINED__ */


#ifndef __ISupportDocUnitSystem_FWD_DEFINED__
#define __ISupportDocUnitSystem_FWD_DEFINED__
typedef interface ISupportDocUnitSystem ISupportDocUnitSystem;

#endif 	/* __ISupportDocUnitSystem_FWD_DEFINED__ */


#ifndef __IUnitServerEventSink_FWD_DEFINED__
#define __IUnitServerEventSink_FWD_DEFINED__
typedef interface IUnitServerEventSink IUnitServerEventSink;

#endif 	/* __IUnitServerEventSink_FWD_DEFINED__ */


#ifndef __IUnitsEventSink_FWD_DEFINED__
#define __IUnitsEventSink_FWD_DEFINED__
typedef interface IUnitsEventSink IUnitsEventSink;

#endif 	/* __IUnitsEventSink_FWD_DEFINED__ */


#ifndef __IUnitTypeEventSink_FWD_DEFINED__
#define __IUnitTypeEventSink_FWD_DEFINED__
typedef interface IUnitTypeEventSink IUnitTypeEventSink;

#endif 	/* __IUnitTypeEventSink_FWD_DEFINED__ */


#ifndef __IUnitTypesEventSink_FWD_DEFINED__
#define __IUnitTypesEventSink_FWD_DEFINED__
typedef interface IUnitTypesEventSink IUnitTypesEventSink;

#endif 	/* __IUnitTypesEventSink_FWD_DEFINED__ */


#ifndef __IDisplayUnitEvents_FWD_DEFINED__
#define __IDisplayUnitEvents_FWD_DEFINED__
typedef interface IDisplayUnitEvents IDisplayUnitEvents;

#endif 	/* __IDisplayUnitEvents_FWD_DEFINED__ */


#ifndef __IDisplayUnitGroupEvents_FWD_DEFINED__
#define __IDisplayUnitGroupEvents_FWD_DEFINED__
typedef interface IDisplayUnitGroupEvents IDisplayUnitGroupEvents;

#endif 	/* __IDisplayUnitGroupEvents_FWD_DEFINED__ */


#ifndef __IDisplayUnitMgrEvents_FWD_DEFINED__
#define __IDisplayUnitMgrEvents_FWD_DEFINED__
typedef interface IDisplayUnitMgrEvents IDisplayUnitMgrEvents;

#endif 	/* __IDisplayUnitMgrEvents_FWD_DEFINED__ */


#ifndef __IUnitSystemEvents_FWD_DEFINED__
#define __IUnitSystemEvents_FWD_DEFINED__
typedef interface IUnitSystemEvents IUnitSystemEvents;

#endif 	/* __IUnitSystemEvents_FWD_DEFINED__ */


#ifndef __IUnitModeControllerEvents_FWD_DEFINED__
#define __IUnitModeControllerEvents_FWD_DEFINED__
typedef interface IUnitModeControllerEvents IUnitModeControllerEvents;

#endif 	/* __IUnitModeControllerEvents_FWD_DEFINED__ */


#ifndef __IDisplayUnitFormatterEvents_FWD_DEFINED__
#define __IDisplayUnitFormatterEvents_FWD_DEFINED__
typedef interface IDisplayUnitFormatterEvents IDisplayUnitFormatterEvents;

#endif 	/* __IDisplayUnitFormatterEvents_FWD_DEFINED__ */


#ifndef __IDocUnitSystemEvents_FWD_DEFINED__
#define __IDocUnitSystemEvents_FWD_DEFINED__
typedef interface IDocUnitSystemEvents IDocUnitSystemEvents;

#endif 	/* __IDocUnitSystemEvents_FWD_DEFINED__ */


#ifndef __DocUnitSystem_FWD_DEFINED__
#define __DocUnitSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class DocUnitSystem DocUnitSystem;
#else
typedef struct DocUnitSystem DocUnitSystem;
#endif /* __cplusplus */

#endif 	/* __DocUnitSystem_FWD_DEFINED__ */


#ifndef __DisplayUnitMgr2_FWD_DEFINED__
#define __DisplayUnitMgr2_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayUnitMgr2 DisplayUnitMgr2;
#else
typedef struct DisplayUnitMgr2 DisplayUnitMgr2;
#endif /* __cplusplus */

#endif 	/* __DisplayUnitMgr2_FWD_DEFINED__ */


#ifndef __AppUnitSystem_FWD_DEFINED__
#define __AppUnitSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class AppUnitSystem AppUnitSystem;
#else
typedef struct AppUnitSystem AppUnitSystem;
#endif /* __cplusplus */

#endif 	/* __AppUnitSystem_FWD_DEFINED__ */


#ifndef __UnitServer_FWD_DEFINED__
#define __UnitServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitServer UnitServer;
#else
typedef struct UnitServer UnitServer;
#endif /* __cplusplus */

#endif 	/* __UnitServer_FWD_DEFINED__ */


#ifndef __UnitModeController_FWD_DEFINED__
#define __UnitModeController_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitModeController UnitModeController;
#else
typedef struct UnitModeController UnitModeController;
#endif /* __cplusplus */

#endif 	/* __UnitModeController_FWD_DEFINED__ */


#ifndef __DisplayUnitFormatter_FWD_DEFINED__
#define __DisplayUnitFormatter_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayUnitFormatter DisplayUnitFormatter;
#else
typedef struct DisplayUnitFormatter DisplayUnitFormatter;
#endif /* __cplusplus */

#endif 	/* __DisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __AnnotatedDisplayUnitFormatter_FWD_DEFINED__
#define __AnnotatedDisplayUnitFormatter_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnnotatedDisplayUnitFormatter AnnotatedDisplayUnitFormatter;
#else
typedef struct AnnotatedDisplayUnitFormatter AnnotatedDisplayUnitFormatter;
#endif /* __cplusplus */

#endif 	/* __AnnotatedDisplayUnitFormatter_FWD_DEFINED__ */


#ifndef __UnitSystem_FWD_DEFINED__
#define __UnitSystem_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitSystem UnitSystem;
#else
typedef struct UnitSystem UnitSystem;
#endif /* __cplusplus */

#endif 	/* __UnitSystem_FWD_DEFINED__ */


#ifndef __DisplayUnitMgr_FWD_DEFINED__
#define __DisplayUnitMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayUnitMgr DisplayUnitMgr;
#else
typedef struct DisplayUnitMgr DisplayUnitMgr;
#endif /* __cplusplus */

#endif 	/* __DisplayUnitMgr_FWD_DEFINED__ */


#ifndef __Unit_FWD_DEFINED__
#define __Unit_FWD_DEFINED__

#ifdef __cplusplus
typedef class Unit Unit;
#else
typedef struct Unit Unit;
#endif /* __cplusplus */

#endif 	/* __Unit_FWD_DEFINED__ */


#ifndef __Units_FWD_DEFINED__
#define __Units_FWD_DEFINED__

#ifdef __cplusplus
typedef class Units Units;
#else
typedef struct Units Units;
#endif /* __cplusplus */

#endif 	/* __Units_FWD_DEFINED__ */


#ifndef __UnitType_FWD_DEFINED__
#define __UnitType_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitType UnitType;
#else
typedef struct UnitType UnitType;
#endif /* __cplusplus */

#endif 	/* __UnitType_FWD_DEFINED__ */


#ifndef __UnitTypes_FWD_DEFINED__
#define __UnitTypes_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitTypes UnitTypes;
#else
typedef struct UnitTypes UnitTypes;
#endif /* __cplusplus */

#endif 	/* __UnitTypes_FWD_DEFINED__ */


#ifndef __DisplayUnit_FWD_DEFINED__
#define __DisplayUnit_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayUnit DisplayUnit;
#else
typedef struct DisplayUnit DisplayUnit;
#endif /* __cplusplus */

#endif 	/* __DisplayUnit_FWD_DEFINED__ */


#ifndef __DisplayUnitGroup_FWD_DEFINED__
#define __DisplayUnitGroup_FWD_DEFINED__

#ifdef __cplusplus
typedef class DisplayUnitGroup DisplayUnitGroup;
#else
typedef struct DisplayUnitGroup DisplayUnitGroup;
#endif /* __cplusplus */

#endif 	/* __DisplayUnitGroup_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WbflUnitServer_0000_0000 */
/* [local] */ 

#define UNITS_E_BASEUNITSSET           MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,512)
#define UNITS_E_BADUNITTYPE            MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,513)
#define UNITS_E_BADUNITTAG             MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,514)
#define UNITS_E_UNITTYPEMISMATCH       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,515)
#define UNITS_E_UNITTYPEALREADYDEFINED MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,516)
#define UNITS_E_UNITALREADYDEFINED     MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,517)
#define UNITS_E_UNITSERVERSET          MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,518)
#define UNITS_E_GROUPALREADYDEFINED    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,519)
#define UNITS_E_BADDISPLAYUNITGROUP    MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,520)
#define UNITS_E_DEFAULTNOTFOUND        MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,521)
#define UNITS_E_APPUNITSYSNOTSET       MAKE_HRESULT(SEVERITY_ERROR,FACILITY_ITF,522)
typedef /* [public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("24A18719-E49F-11d3-8A40-006097C68A9C") 
enum __MIDL___MIDL_itf_WbflUnitServer_0000_0000_0001
    {
        nftAutomatic	= 1,
        nftFixed	= 2,
        nftScientific	= 3,
        nftEngineering	= 4
    } 	NumericFormatType;

typedef /* [public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("1DAA99B8-E4B3-11d3-8A40-006097C68A9C") 
enum __MIDL___MIDL_itf_WbflUnitServer_0000_0000_0002
    {
        tjLeft	= 1,
        tjRight	= 2
    } 	TextJustificationType;



extern RPC_IF_HANDLE __MIDL_itf_WbflUnitServer_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WbflUnitServer_0000_0000_v0_0_s_ifspec;

#ifndef __IDisplayUnitFormatter_INTERFACE_DEFINED__
#define __IDisplayUnitFormatter_INTERFACE_DEFINED__

/* interface IDisplayUnitFormatter */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDisplayUnitFormatter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D934CE44-CB38-11d3-8CE1-A85CC0A0E770")
    IDisplayUnitFormatter : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE FormatSpecifiers( 
            /* [in] */ Uint32 width,
            /* [in] */ Uint32 precision,
            /* [in] */ TextJustificationType justify,
            /* [in] */ NumericFormatType fmt,
            /* [in] */ Float64 zeroVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ Uint32 *val) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Precision( 
            /* [retval][out] */ Uint32 *val) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Notation( 
            /* [retval][out] */ NumericFormatType *notation) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Justification( 
            /* [retval][out] */ TextJustificationType *justify) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ZeroTolerance( 
            /* [retval][out] */ Float64 *zeroTol) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Format( 
            /* [in] */ Float64 val,
            /* [in] */ BSTR tag,
            /* [retval][out] */ BSTR *fmtString) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UsesTag( 
            /* [retval][out] */ VARIANT_BOOL *bUsesTag) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitFormatterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitFormatter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitFormatter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitFormatter * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *FormatSpecifiers )( 
            IDisplayUnitFormatter * This,
            /* [in] */ Uint32 width,
            /* [in] */ Uint32 precision,
            /* [in] */ TextJustificationType justify,
            /* [in] */ NumericFormatType fmt,
            /* [in] */ Float64 zeroVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Precision )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Notation )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ NumericFormatType *notation);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Justification )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ TextJustificationType *justify);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroTolerance )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ Float64 *zeroTol);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IDisplayUnitFormatter * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR tag,
            /* [retval][out] */ BSTR *fmtString);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UsesTag )( 
            IDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *bUsesTag);
        
        END_INTERFACE
    } IDisplayUnitFormatterVtbl;

    interface IDisplayUnitFormatter
    {
        CONST_VTBL struct IDisplayUnitFormatterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitFormatter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitFormatter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitFormatter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitFormatter_FormatSpecifiers(This,width,precision,justify,fmt,zeroVal)	\
    ( (This)->lpVtbl -> FormatSpecifiers(This,width,precision,justify,fmt,zeroVal) ) 

#define IDisplayUnitFormatter_get_Width(This,val)	\
    ( (This)->lpVtbl -> get_Width(This,val) ) 

#define IDisplayUnitFormatter_get_Precision(This,val)	\
    ( (This)->lpVtbl -> get_Precision(This,val) ) 

#define IDisplayUnitFormatter_get_Notation(This,notation)	\
    ( (This)->lpVtbl -> get_Notation(This,notation) ) 

#define IDisplayUnitFormatter_get_Justification(This,justify)	\
    ( (This)->lpVtbl -> get_Justification(This,justify) ) 

#define IDisplayUnitFormatter_get_ZeroTolerance(This,zeroTol)	\
    ( (This)->lpVtbl -> get_ZeroTolerance(This,zeroTol) ) 

#define IDisplayUnitFormatter_Format(This,val,tag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,tag,fmtString) ) 

#define IDisplayUnitFormatter_get_UsesTag(This,bUsesTag)	\
    ( (This)->lpVtbl -> get_UsesTag(This,bUsesTag) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitFormatter_INTERFACE_DEFINED__ */


#ifndef __IAnnotatedDisplayUnitFormatter_INTERFACE_DEFINED__
#define __IAnnotatedDisplayUnitFormatter_INTERFACE_DEFINED__

/* interface IAnnotatedDisplayUnitFormatter */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAnnotatedDisplayUnitFormatter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("61E29B40-CD8D-11d3-8CE1-926A77670A4E")
    IAnnotatedDisplayUnitFormatter : public IDisplayUnitFormatter
    {
    public:
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_OffsetDigits( 
            /* [in] */ Uint32 nDigits) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_OffsetDigits( 
            /* [retval][out] */ Uint32 *nDigits) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Multiplier( 
            /* [in] */ Float64 multiplier) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Multiplier( 
            /* [retval][out] */ Float64 *multiplier) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_Annotation( 
            /* [in] */ BSTR bstrAnnotation) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Annotation( 
            /* [retval][out] */ BSTR *bstrAnnotation) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAnnotatedDisplayUnitFormatterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnnotatedDisplayUnitFormatter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnnotatedDisplayUnitFormatter * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *FormatSpecifiers )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ Uint32 width,
            /* [in] */ Uint32 precision,
            /* [in] */ TextJustificationType justify,
            /* [in] */ NumericFormatType fmt,
            /* [in] */ Float64 zeroVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Precision )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *val);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Notation )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ NumericFormatType *notation);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Justification )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ TextJustificationType *justify);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ZeroTolerance )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ Float64 *zeroTol);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR tag,
            /* [retval][out] */ BSTR *fmtString);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UsesTag )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ VARIANT_BOOL *bUsesTag);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OffsetDigits )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ Uint32 nDigits);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OffsetDigits )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ Uint32 *nDigits);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Multiplier )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ Float64 multiplier);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Multiplier )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ Float64 *multiplier);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Annotation )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [in] */ BSTR bstrAnnotation);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Annotation )( 
            IAnnotatedDisplayUnitFormatter * This,
            /* [retval][out] */ BSTR *bstrAnnotation);
        
        END_INTERFACE
    } IAnnotatedDisplayUnitFormatterVtbl;

    interface IAnnotatedDisplayUnitFormatter
    {
        CONST_VTBL struct IAnnotatedDisplayUnitFormatterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnnotatedDisplayUnitFormatter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAnnotatedDisplayUnitFormatter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAnnotatedDisplayUnitFormatter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAnnotatedDisplayUnitFormatter_FormatSpecifiers(This,width,precision,justify,fmt,zeroVal)	\
    ( (This)->lpVtbl -> FormatSpecifiers(This,width,precision,justify,fmt,zeroVal) ) 

#define IAnnotatedDisplayUnitFormatter_get_Width(This,val)	\
    ( (This)->lpVtbl -> get_Width(This,val) ) 

#define IAnnotatedDisplayUnitFormatter_get_Precision(This,val)	\
    ( (This)->lpVtbl -> get_Precision(This,val) ) 

#define IAnnotatedDisplayUnitFormatter_get_Notation(This,notation)	\
    ( (This)->lpVtbl -> get_Notation(This,notation) ) 

#define IAnnotatedDisplayUnitFormatter_get_Justification(This,justify)	\
    ( (This)->lpVtbl -> get_Justification(This,justify) ) 

#define IAnnotatedDisplayUnitFormatter_get_ZeroTolerance(This,zeroTol)	\
    ( (This)->lpVtbl -> get_ZeroTolerance(This,zeroTol) ) 

#define IAnnotatedDisplayUnitFormatter_Format(This,val,tag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,tag,fmtString) ) 

#define IAnnotatedDisplayUnitFormatter_get_UsesTag(This,bUsesTag)	\
    ( (This)->lpVtbl -> get_UsesTag(This,bUsesTag) ) 


#define IAnnotatedDisplayUnitFormatter_put_OffsetDigits(This,nDigits)	\
    ( (This)->lpVtbl -> put_OffsetDigits(This,nDigits) ) 

#define IAnnotatedDisplayUnitFormatter_get_OffsetDigits(This,nDigits)	\
    ( (This)->lpVtbl -> get_OffsetDigits(This,nDigits) ) 

#define IAnnotatedDisplayUnitFormatter_put_Multiplier(This,multiplier)	\
    ( (This)->lpVtbl -> put_Multiplier(This,multiplier) ) 

#define IAnnotatedDisplayUnitFormatter_get_Multiplier(This,multiplier)	\
    ( (This)->lpVtbl -> get_Multiplier(This,multiplier) ) 

#define IAnnotatedDisplayUnitFormatter_put_Annotation(This,bstrAnnotation)	\
    ( (This)->lpVtbl -> put_Annotation(This,bstrAnnotation) ) 

#define IAnnotatedDisplayUnitFormatter_get_Annotation(This,bstrAnnotation)	\
    ( (This)->lpVtbl -> get_Annotation(This,bstrAnnotation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAnnotatedDisplayUnitFormatter_INTERFACE_DEFINED__ */



#ifndef __WBFLUnitServer_LIBRARY_DEFINED__
#define __WBFLUnitServer_LIBRARY_DEFINED__

/* library WBFLUnitServer */
/* [helpstring][helpcontext][helpfile][version][uuid] */ 

typedef /* [public][public][public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("6F535332-84A0-11d2-887D-006097C68A9C") 
enum __MIDL___MIDL_itf_WbflUnitServer_0000_0002_0001
    {
        unitsSI	= 1,
        unitsUS	= 2,
        unitsAll	= 3
    } 	UnitSystemType;

typedef /* [public][public][public][public][public][public][public][uuid][helpcontext][helpstring][public] */  DECLSPEC_UUID("E1744920-CB90-11d3-8CE1-A85CC0A0E770") 
enum __MIDL___MIDL_itf_WbflUnitServer_0000_0002_0002
    {
        umSI	= 1,
        umUS	= 2
    } 	UnitModeType;

typedef /* [public][uuid][helpstring][public] */  DECLSPEC_UUID("81F8CB89-1C2B-4196-9936-7B471F57FFB5") 
enum __MIDL___MIDL_itf_WbflUnitServer_0000_0002_0003
    {
        suSI	= 1,
        suUS	= 2
    } 	SpecUnitType;






EXTERN_C const IID LIBID_WBFLUnitServer;

#ifndef __IUnits_INTERFACE_DEFINED__
#define __IUnits_INTERFACE_DEFINED__

/* interface IUnits */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("641DCEA1-19D1-11D2-8D11-94FA07C10000")
    IUnits : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IUnit **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR tag,
            /* [in] */ Float64 preTerm,
            /* [in] */ Float64 cf,
            /* [in] */ Float64 postTerm,
            /* [in] */ UnitSystemType unitSystem,
            /* [retval][out] */ IUnit **ppUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Index) = 0;
        
        virtual /* [helpstring][helpcontext][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumUnits( 
            /* [retval][out] */ IEnumUnits **enumUnits) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnits * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnits * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IUnits * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IUnit **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IUnits * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IUnits * This,
            /* [retval][out] */ CollectionIndexType *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IUnits * This,
            /* [in] */ BSTR tag,
            /* [in] */ Float64 preTerm,
            /* [in] */ Float64 cf,
            /* [in] */ Float64 postTerm,
            /* [in] */ UnitSystemType unitSystem,
            /* [retval][out] */ IUnit **ppUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IUnits * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IUnits * This,
            /* [in] */ VARIANT Index);
        
        /* [helpstring][helpcontext][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumUnits )( 
            IUnits * This,
            /* [retval][out] */ IEnumUnits **enumUnits);
        
        END_INTERFACE
    } IUnitsVtbl;

    interface IUnits
    {
        CONST_VTBL struct IUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnits_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnits_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnits_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnits_get_Item(This,Index,retval)	\
    ( (This)->lpVtbl -> get_Item(This,Index,retval) ) 

#define IUnits_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IUnits_get_Count(This,retval)	\
    ( (This)->lpVtbl -> get_Count(This,retval) ) 

#define IUnits_Add(This,tag,preTerm,cf,postTerm,unitSystem,ppUnit)	\
    ( (This)->lpVtbl -> Add(This,tag,preTerm,cf,postTerm,unitSystem,ppUnit) ) 

#define IUnits_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IUnits_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define IUnits_get__EnumUnits(This,enumUnits)	\
    ( (This)->lpVtbl -> get__EnumUnits(This,enumUnits) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnits_INTERFACE_DEFINED__ */


#ifndef __IUnitServer_INTERFACE_DEFINED__
#define __IUnitServer_INTERFACE_DEFINED__

/* interface IUnitServer */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C65F03C3-16AB-11D2-8D11-94FA07C10000")
    IUnitServer : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE SetBaseUnits( 
            /* [in] */ BSTR bstrMass,
            /* [in] */ BSTR bstrLength,
            /* [in] */ BSTR bstrTime,
            /* [in] */ BSTR bstrTemp,
            /* [in] */ BSTR bstrAngle) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mass( 
            /* [retval][out] */ BSTR *pMass) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ BSTR *pLength) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ BSTR *pTime) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Temperature( 
            /* [retval][out] */ BSTR *pTemperature) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ BSTR *pAngle) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitTypes( 
            /* [retval][out] */ IUnitTypes **ppUnitTypes) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitConvert( 
            /* [retval][out] */ IUnitConvert **convert) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitConvert2( 
            /* [retval][out] */ IUnitConvert2 **convert) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitServer * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *SetBaseUnits )( 
            IUnitServer * This,
            /* [in] */ BSTR bstrMass,
            /* [in] */ BSTR bstrLength,
            /* [in] */ BSTR bstrTime,
            /* [in] */ BSTR bstrTemp,
            /* [in] */ BSTR bstrAngle);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mass )( 
            IUnitServer * This,
            /* [retval][out] */ BSTR *pMass);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IUnitServer * This,
            /* [retval][out] */ BSTR *pLength);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            IUnitServer * This,
            /* [retval][out] */ BSTR *pTime);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Temperature )( 
            IUnitServer * This,
            /* [retval][out] */ BSTR *pTemperature);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IUnitServer * This,
            /* [retval][out] */ BSTR *pAngle);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitTypes )( 
            IUnitServer * This,
            /* [retval][out] */ IUnitTypes **ppUnitTypes);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitConvert )( 
            IUnitServer * This,
            /* [retval][out] */ IUnitConvert **convert);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitConvert2 )( 
            IUnitServer * This,
            /* [retval][out] */ IUnitConvert2 **convert);
        
        END_INTERFACE
    } IUnitServerVtbl;

    interface IUnitServer
    {
        CONST_VTBL struct IUnitServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitServer_SetBaseUnits(This,bstrMass,bstrLength,bstrTime,bstrTemp,bstrAngle)	\
    ( (This)->lpVtbl -> SetBaseUnits(This,bstrMass,bstrLength,bstrTime,bstrTemp,bstrAngle) ) 

#define IUnitServer_get_Mass(This,pMass)	\
    ( (This)->lpVtbl -> get_Mass(This,pMass) ) 

#define IUnitServer_get_Length(This,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,pLength) ) 

#define IUnitServer_get_Time(This,pTime)	\
    ( (This)->lpVtbl -> get_Time(This,pTime) ) 

#define IUnitServer_get_Temperature(This,pTemperature)	\
    ( (This)->lpVtbl -> get_Temperature(This,pTemperature) ) 

#define IUnitServer_get_Angle(This,pAngle)	\
    ( (This)->lpVtbl -> get_Angle(This,pAngle) ) 

#define IUnitServer_get_UnitTypes(This,ppUnitTypes)	\
    ( (This)->lpVtbl -> get_UnitTypes(This,ppUnitTypes) ) 

#define IUnitServer_get_UnitConvert(This,convert)	\
    ( (This)->lpVtbl -> get_UnitConvert(This,convert) ) 

#define IUnitServer_get_UnitConvert2(This,convert)	\
    ( (This)->lpVtbl -> get_UnitConvert2(This,convert) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitServer_INTERFACE_DEFINED__ */


#ifndef __IUnitConvert_INTERFACE_DEFINED__
#define __IUnitConvert_INTERFACE_DEFINED__

/* interface IUnitConvert */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitConvert;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45FEDF40-79AD-11d2-8D11-50830CC10000")
    IUnitConvert : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Convert( 
            /* [in] */ Float64 From,
            /* [in] */ BSTR fromUnit,
            /* [in] */ BSTR toUnit,
            /* [retval][out] */ Float64 *pTo) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertToBaseUnits( 
            /* [in] */ Float64 val,
            /* [in] */ BSTR fromUnit,
            /* [retval][out] */ Float64 *pConvVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertFromBaseUnits( 
            /* [in] */ Float64 val,
            /* [in] */ BSTR toUnit,
            /* [retval][out] */ Float64 *pConvVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitConvertVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitConvert * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitConvert * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitConvert * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Convert )( 
            IUnitConvert * This,
            /* [in] */ Float64 From,
            /* [in] */ BSTR fromUnit,
            /* [in] */ BSTR toUnit,
            /* [retval][out] */ Float64 *pTo);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertToBaseUnits )( 
            IUnitConvert * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR fromUnit,
            /* [retval][out] */ Float64 *pConvVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromBaseUnits )( 
            IUnitConvert * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR toUnit,
            /* [retval][out] */ Float64 *pConvVal);
        
        END_INTERFACE
    } IUnitConvertVtbl;

    interface IUnitConvert
    {
        CONST_VTBL struct IUnitConvertVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitConvert_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitConvert_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitConvert_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitConvert_Convert(This,From,fromUnit,toUnit,pTo)	\
    ( (This)->lpVtbl -> Convert(This,From,fromUnit,toUnit,pTo) ) 

#define IUnitConvert_ConvertToBaseUnits(This,val,fromUnit,pConvVal)	\
    ( (This)->lpVtbl -> ConvertToBaseUnits(This,val,fromUnit,pConvVal) ) 

#define IUnitConvert_ConvertFromBaseUnits(This,val,toUnit,pConvVal)	\
    ( (This)->lpVtbl -> ConvertFromBaseUnits(This,val,toUnit,pConvVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitConvert_INTERFACE_DEFINED__ */


#ifndef __IUnitConvert2_INTERFACE_DEFINED__
#define __IUnitConvert2_INTERFACE_DEFINED__

/* interface IUnitConvert2 */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitConvert2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45FEDF41-79AD-11d2-8D11-50830CC10000")
    IUnitConvert2 : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Convert( 
            /* [in] */ Float64 From,
            /* [in] */ IUnit *pFromUnit,
            /* [in] */ IUnit *pToUnit,
            /* [retval][out] */ Float64 *pTo) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertToBaseUnits( 
            /* [in] */ Float64 val,
            /* [in] */ IUnit *pFromUnit,
            /* [retval][out] */ Float64 *pConvVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertFromBaseUnits( 
            /* [in] */ Float64 val,
            /* [in] */ IUnit *pToUnit,
            /* [retval][out] */ Float64 *pConvVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitConvert2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitConvert2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitConvert2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitConvert2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Convert )( 
            IUnitConvert2 * This,
            /* [in] */ Float64 From,
            /* [in] */ IUnit *pFromUnit,
            /* [in] */ IUnit *pToUnit,
            /* [retval][out] */ Float64 *pTo);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertToBaseUnits )( 
            IUnitConvert2 * This,
            /* [in] */ Float64 val,
            /* [in] */ IUnit *pFromUnit,
            /* [retval][out] */ Float64 *pConvVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromBaseUnits )( 
            IUnitConvert2 * This,
            /* [in] */ Float64 val,
            /* [in] */ IUnit *pToUnit,
            /* [retval][out] */ Float64 *pConvVal);
        
        END_INTERFACE
    } IUnitConvert2Vtbl;

    interface IUnitConvert2
    {
        CONST_VTBL struct IUnitConvert2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitConvert2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitConvert2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitConvert2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitConvert2_Convert(This,From,pFromUnit,pToUnit,pTo)	\
    ( (This)->lpVtbl -> Convert(This,From,pFromUnit,pToUnit,pTo) ) 

#define IUnitConvert2_ConvertToBaseUnits(This,val,pFromUnit,pConvVal)	\
    ( (This)->lpVtbl -> ConvertToBaseUnits(This,val,pFromUnit,pConvVal) ) 

#define IUnitConvert2_ConvertFromBaseUnits(This,val,pToUnit,pConvVal)	\
    ( (This)->lpVtbl -> ConvertFromBaseUnits(This,val,pToUnit,pConvVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitConvert2_INTERFACE_DEFINED__ */


#ifndef __IUnitType_INTERFACE_DEFINED__
#define __IUnitType_INTERFACE_DEFINED__

/* interface IUnitType */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6474060-7E6F-11d2-8D11-50830CC10000")
    IUnitType : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Label( 
            /* [retval][out] */ BSTR *pLabel) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Mass( 
            /* [retval][out] */ Float64 *pMass) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Length( 
            /* [retval][out] */ Float64 *pLength) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ Float64 *pTime) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Temperature( 
            /* [retval][out] */ Float64 *pTemperature) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ Float64 *pAngle) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Units( 
            /* [retval][out] */ IUnits **ppUnits) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitServer( 
            /* [retval][out] */ IUnitServer **unitServer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitType * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitType * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitType * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Label )( 
            IUnitType * This,
            /* [retval][out] */ BSTR *pLabel);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mass )( 
            IUnitType * This,
            /* [retval][out] */ Float64 *pMass);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Length )( 
            IUnitType * This,
            /* [retval][out] */ Float64 *pLength);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            IUnitType * This,
            /* [retval][out] */ Float64 *pTime);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Temperature )( 
            IUnitType * This,
            /* [retval][out] */ Float64 *pTemperature);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IUnitType * This,
            /* [retval][out] */ Float64 *pAngle);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Units )( 
            IUnitType * This,
            /* [retval][out] */ IUnits **ppUnits);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitServer )( 
            IUnitType * This,
            /* [retval][out] */ IUnitServer **unitServer);
        
        END_INTERFACE
    } IUnitTypeVtbl;

    interface IUnitType
    {
        CONST_VTBL struct IUnitTypeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitType_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitType_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitType_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitType_get_Label(This,pLabel)	\
    ( (This)->lpVtbl -> get_Label(This,pLabel) ) 

#define IUnitType_get_Mass(This,pMass)	\
    ( (This)->lpVtbl -> get_Mass(This,pMass) ) 

#define IUnitType_get_Length(This,pLength)	\
    ( (This)->lpVtbl -> get_Length(This,pLength) ) 

#define IUnitType_get_Time(This,pTime)	\
    ( (This)->lpVtbl -> get_Time(This,pTime) ) 

#define IUnitType_get_Temperature(This,pTemperature)	\
    ( (This)->lpVtbl -> get_Temperature(This,pTemperature) ) 

#define IUnitType_get_Angle(This,pAngle)	\
    ( (This)->lpVtbl -> get_Angle(This,pAngle) ) 

#define IUnitType_get_Units(This,ppUnits)	\
    ( (This)->lpVtbl -> get_Units(This,ppUnits) ) 

#define IUnitType_get_UnitServer(This,unitServer)	\
    ( (This)->lpVtbl -> get_UnitServer(This,unitServer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitType_INTERFACE_DEFINED__ */


#ifndef __IEnumUnitTypes_INTERFACE_DEFINED__
#define __IEnumUnitTypes_INTERFACE_DEFINED__

/* interface IEnumUnitTypes */
/* [unique][oleautomation][restricted][hidden][uuid][object] */ 


EXTERN_C const IID IID_IEnumUnitTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5CEF7DC0-B6A3-11d3-8CDF-C9DF305B3C59")
    IEnumUnitTypes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumUnitTypes **enumUnitTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IUnitType **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumUnitTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumUnitTypes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumUnitTypes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumUnitTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumUnitTypes * This,
            /* [out] */ IEnumUnitTypes **enumUnitTypes);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumUnitTypes * This,
            /* [in] */ ULONG celt,
            /* [out] */ IUnitType **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumUnitTypes * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumUnitTypes * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumUnitTypesVtbl;

    interface IEnumUnitTypes
    {
        CONST_VTBL struct IEnumUnitTypesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumUnitTypes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumUnitTypes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumUnitTypes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumUnitTypes_Clone(This,enumUnitTypes)	\
    ( (This)->lpVtbl -> Clone(This,enumUnitTypes) ) 

#define IEnumUnitTypes_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumUnitTypes_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumUnitTypes_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumUnitTypes_INTERFACE_DEFINED__ */


#ifndef __IUnitTypes_INTERFACE_DEFINED__
#define __IUnitTypes_INTERFACE_DEFINED__

/* interface IUnitTypes */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A03A9440-7E76-11d2-8D11-50830CC10000")
    IUnitTypes : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IUnitType **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR label,
            /* [in] */ Float64 m,
            /* [in] */ Float64 l,
            /* [in] */ Float64 t,
            /* [in] */ Float64 k,
            /* [in] */ Float64 a,
            /* [retval][out] */ IUnitType **ppUnitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT Index) = 0;
        
        virtual /* [helpstring][helpcontext][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumUnitTypes( 
            /* [retval][out] */ IEnumUnitTypes **enumUnitTypes) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitTypes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitTypes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitTypes * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IUnitTypes * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IUnitType **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IUnitTypes * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IUnitTypes * This,
            /* [retval][out] */ CollectionIndexType *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IUnitTypes * This,
            /* [in] */ BSTR label,
            /* [in] */ Float64 m,
            /* [in] */ Float64 l,
            /* [in] */ Float64 t,
            /* [in] */ Float64 k,
            /* [in] */ Float64 a,
            /* [retval][out] */ IUnitType **ppUnitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IUnitTypes * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IUnitTypes * This,
            VARIANT Index);
        
        /* [helpstring][helpcontext][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumUnitTypes )( 
            IUnitTypes * This,
            /* [retval][out] */ IEnumUnitTypes **enumUnitTypes);
        
        END_INTERFACE
    } IUnitTypesVtbl;

    interface IUnitTypes
    {
        CONST_VTBL struct IUnitTypesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitTypes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitTypes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitTypes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitTypes_get_Item(This,Index,retval)	\
    ( (This)->lpVtbl -> get_Item(This,Index,retval) ) 

#define IUnitTypes_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IUnitTypes_get_Count(This,retval)	\
    ( (This)->lpVtbl -> get_Count(This,retval) ) 

#define IUnitTypes_Add(This,label,m,l,t,k,a,ppUnitType)	\
    ( (This)->lpVtbl -> Add(This,label,m,l,t,k,a,ppUnitType) ) 

#define IUnitTypes_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IUnitTypes_Remove(This,Index)	\
    ( (This)->lpVtbl -> Remove(This,Index) ) 

#define IUnitTypes_get__EnumUnitTypes(This,enumUnitTypes)	\
    ( (This)->lpVtbl -> get__EnumUnitTypes(This,enumUnitTypes) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitTypes_INTERFACE_DEFINED__ */


#ifndef __IUnit_INTERFACE_DEFINED__
#define __IUnit_INTERFACE_DEFINED__

/* interface IUnit */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E38A041A-7F25-11d2-885B-006097C68A9C")
    IUnit : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PreTerm( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_ConvFactor( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_PostTerm( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitSystem( 
            /* [retval][out] */ UnitSystemType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitType( 
            /* [retval][out] */ IUnitType **ppUnitType) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitServer( 
            /* [retval][out] */ IUnitServer **unitServer) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnit * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tag )( 
            IUnit * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PreTerm )( 
            IUnit * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvFactor )( 
            IUnit * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PostTerm )( 
            IUnit * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitSystem )( 
            IUnit * This,
            /* [retval][out] */ UnitSystemType *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitType )( 
            IUnit * This,
            /* [retval][out] */ IUnitType **ppUnitType);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitServer )( 
            IUnit * This,
            /* [retval][out] */ IUnitServer **unitServer);
        
        END_INTERFACE
    } IUnitVtbl;

    interface IUnit
    {
        CONST_VTBL struct IUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnit_get_Tag(This,pVal)	\
    ( (This)->lpVtbl -> get_Tag(This,pVal) ) 

#define IUnit_get_PreTerm(This,pVal)	\
    ( (This)->lpVtbl -> get_PreTerm(This,pVal) ) 

#define IUnit_get_ConvFactor(This,pVal)	\
    ( (This)->lpVtbl -> get_ConvFactor(This,pVal) ) 

#define IUnit_get_PostTerm(This,pVal)	\
    ( (This)->lpVtbl -> get_PostTerm(This,pVal) ) 

#define IUnit_get_UnitSystem(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitSystem(This,pVal) ) 

#define IUnit_get_UnitType(This,ppUnitType)	\
    ( (This)->lpVtbl -> get_UnitType(This,ppUnitType) ) 

#define IUnit_get_UnitServer(This,unitServer)	\
    ( (This)->lpVtbl -> get_UnitServer(This,unitServer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnit_INTERFACE_DEFINED__ */


#ifndef __IEnumUnits_INTERFACE_DEFINED__
#define __IEnumUnits_INTERFACE_DEFINED__

/* interface IEnumUnits */
/* [unique][oleautomation][restricted][hidden][uuid][object] */ 


EXTERN_C const IID IID_IEnumUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F7D82A0-B6A4-11d3-8CDF-C9DF305B3C59")
    IEnumUnits : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumUnits **enumUnits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IUnit **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumUnits * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumUnits * This,
            /* [out] */ IEnumUnits **enumUnits);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumUnits * This,
            /* [in] */ ULONG celt,
            /* [out] */ IUnit **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumUnits * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumUnitsVtbl;

    interface IEnumUnits
    {
        CONST_VTBL struct IEnumUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumUnits_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumUnits_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumUnits_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumUnits_Clone(This,enumUnits)	\
    ( (This)->lpVtbl -> Clone(This,enumUnits) ) 

#define IEnumUnits_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumUnits_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumUnits_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumUnits_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnit_INTERFACE_DEFINED__
#define __IDisplayUnit_INTERFACE_DEFINED__

/* interface IDisplayUnit */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDisplayUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D934CE43-CB38-11d3-8CE1-A85CC0A0E770")
    IDisplayUnit : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Formatter( 
            /* [retval][out] */ IDisplayUnitFormatter **formatter) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_Formatter( 
            /* [in] */ IDisplayUnitFormatter *formatter) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Unit( 
            /* [retval][out] */ IUnit **unit) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitTag( 
            /* [retval][out] */ BSTR *unitTag) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitSystem( 
            /* [retval][out] */ UnitSystemType *unitSystem) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE IsDefault( 
            /* [retval][out] */ VARIANT_BOOL *bIsDefault) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Format( 
            /* [in] */ Float64 val,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnit * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Formatter )( 
            IDisplayUnit * This,
            /* [retval][out] */ IDisplayUnitFormatter **formatter);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Formatter )( 
            IDisplayUnit * This,
            /* [in] */ IDisplayUnitFormatter *formatter);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Unit )( 
            IDisplayUnit * This,
            /* [retval][out] */ IUnit **unit);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitTag )( 
            IDisplayUnit * This,
            /* [retval][out] */ BSTR *unitTag);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitSystem )( 
            IDisplayUnit * This,
            /* [retval][out] */ UnitSystemType *unitSystem);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *IsDefault )( 
            IDisplayUnit * This,
            /* [retval][out] */ VARIANT_BOOL *bIsDefault);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IDisplayUnit * This,
            /* [in] */ Float64 val,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString);
        
        END_INTERFACE
    } IDisplayUnitVtbl;

    interface IDisplayUnit
    {
        CONST_VTBL struct IDisplayUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnit_get_Formatter(This,formatter)	\
    ( (This)->lpVtbl -> get_Formatter(This,formatter) ) 

#define IDisplayUnit_putref_Formatter(This,formatter)	\
    ( (This)->lpVtbl -> putref_Formatter(This,formatter) ) 

#define IDisplayUnit_get_Unit(This,unit)	\
    ( (This)->lpVtbl -> get_Unit(This,unit) ) 

#define IDisplayUnit_get_UnitTag(This,unitTag)	\
    ( (This)->lpVtbl -> get_UnitTag(This,unitTag) ) 

#define IDisplayUnit_get_UnitSystem(This,unitSystem)	\
    ( (This)->lpVtbl -> get_UnitSystem(This,unitSystem) ) 

#define IDisplayUnit_IsDefault(This,bIsDefault)	\
    ( (This)->lpVtbl -> IsDefault(This,bIsDefault) ) 

#define IDisplayUnit_Format(This,val,bShowUnitTag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,bShowUnitTag,fmtString) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnit_INTERFACE_DEFINED__ */


#ifndef __IEnumDisplayUnits_INTERFACE_DEFINED__
#define __IEnumDisplayUnits_INTERFACE_DEFINED__

/* interface IEnumDisplayUnits */
/* [unique][oleautomation][restricted][hidden][uuid][object] */ 


EXTERN_C const IID IID_IEnumDisplayUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD8E6EC0-D044-11d3-8CE1-F3DE57DF1F4D")
    IEnumDisplayUnits : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDisplayUnits **enumUnits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IDisplayUnit **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumDisplayUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDisplayUnits * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDisplayUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDisplayUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDisplayUnits * This,
            /* [out] */ IEnumDisplayUnits **enumUnits);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDisplayUnits * This,
            /* [in] */ ULONG celt,
            /* [out] */ IDisplayUnit **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDisplayUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDisplayUnits * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumDisplayUnitsVtbl;

    interface IEnumDisplayUnits
    {
        CONST_VTBL struct IEnumDisplayUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDisplayUnits_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumDisplayUnits_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumDisplayUnits_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumDisplayUnits_Clone(This,enumUnits)	\
    ( (This)->lpVtbl -> Clone(This,enumUnits) ) 

#define IEnumDisplayUnits_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumDisplayUnits_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumDisplayUnits_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumDisplayUnits_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitGroup_INTERFACE_DEFINED__
#define __IDisplayUnitGroup_INTERFACE_DEFINED__

/* interface IDisplayUnitGroup */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDisplayUnitGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D934CE41-CB38-11d3-8CE1-A85CC0A0E770")
    IDisplayUnitGroup : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *name) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitType( 
            /* [retval][out] */ BSTR *unitType) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR unitTag,
            /* [retval][out] */ IDisplayUnit **retval) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR unitTag,
            /* [in] */ UnitSystemType unitSystem,
            /* [in] */ IDisplayUnitFormatter *formatter,
            /* [in] */ VARIANT_BOOL bDefault,
            /* [retval][out] */ IDisplayUnit **dispUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR unitTag) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Default( 
            UnitModeType unitMode,
            /* [retval][out] */ IDisplayUnit **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumDisplayUnits( 
            /* [retval][out] */ IEnumDisplayUnits **enumDisplayUnits) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitGroup * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitGroup * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IDisplayUnitGroup * This,
            /* [retval][out] */ BSTR *name);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitType )( 
            IDisplayUnitGroup * This,
            /* [retval][out] */ BSTR *unitType);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDisplayUnitGroup * This,
            /* [in] */ BSTR unitTag,
            /* [retval][out] */ IDisplayUnit **retval);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDisplayUnitGroup * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDisplayUnitGroup * This,
            /* [retval][out] */ CollectionIndexType *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDisplayUnitGroup * This,
            /* [in] */ BSTR unitTag,
            /* [in] */ UnitSystemType unitSystem,
            /* [in] */ IDisplayUnitFormatter *formatter,
            /* [in] */ VARIANT_BOOL bDefault,
            /* [retval][out] */ IDisplayUnit **dispUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDisplayUnitGroup * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDisplayUnitGroup * This,
            /* [in] */ BSTR unitTag);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Default )( 
            IDisplayUnitGroup * This,
            UnitModeType unitMode,
            /* [retval][out] */ IDisplayUnit **pVal);
        
        /* [helpstring][helpcontext][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumDisplayUnits )( 
            IDisplayUnitGroup * This,
            /* [retval][out] */ IEnumDisplayUnits **enumDisplayUnits);
        
        END_INTERFACE
    } IDisplayUnitGroupVtbl;

    interface IDisplayUnitGroup
    {
        CONST_VTBL struct IDisplayUnitGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitGroup_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitGroup_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitGroup_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitGroup_get_Name(This,name)	\
    ( (This)->lpVtbl -> get_Name(This,name) ) 

#define IDisplayUnitGroup_get_UnitType(This,unitType)	\
    ( (This)->lpVtbl -> get_UnitType(This,unitType) ) 

#define IDisplayUnitGroup_get_Item(This,unitTag,retval)	\
    ( (This)->lpVtbl -> get_Item(This,unitTag,retval) ) 

#define IDisplayUnitGroup_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDisplayUnitGroup_get_Count(This,retval)	\
    ( (This)->lpVtbl -> get_Count(This,retval) ) 

#define IDisplayUnitGroup_Add(This,unitTag,unitSystem,formatter,bDefault,dispUnit)	\
    ( (This)->lpVtbl -> Add(This,unitTag,unitSystem,formatter,bDefault,dispUnit) ) 

#define IDisplayUnitGroup_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDisplayUnitGroup_Remove(This,unitTag)	\
    ( (This)->lpVtbl -> Remove(This,unitTag) ) 

#define IDisplayUnitGroup_get_Default(This,unitMode,pVal)	\
    ( (This)->lpVtbl -> get_Default(This,unitMode,pVal) ) 

#define IDisplayUnitGroup_get__EnumDisplayUnits(This,enumDisplayUnits)	\
    ( (This)->lpVtbl -> get__EnumDisplayUnits(This,enumDisplayUnits) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitGroup_INTERFACE_DEFINED__ */


#ifndef __IEnumDisplayUnitGroups_INTERFACE_DEFINED__
#define __IEnumDisplayUnitGroups_INTERFACE_DEFINED__

/* interface IEnumDisplayUnitGroups */
/* [unique][oleautomation][restricted][hidden][uuid][object] */ 


EXTERN_C const IID IID_IEnumDisplayUnitGroups;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FD8E6EC1-D044-11d3-8CE1-F3DE57DF1F4D")
    IEnumDisplayUnitGroups : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumDisplayUnitGroups **enumUnits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IDisplayUnitGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumDisplayUnitGroupsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumDisplayUnitGroups * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumDisplayUnitGroups * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumDisplayUnitGroups * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumDisplayUnitGroups * This,
            /* [out] */ IEnumDisplayUnitGroups **enumUnits);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumDisplayUnitGroups * This,
            /* [in] */ ULONG celt,
            /* [out] */ IDisplayUnitGroup **rgelt,
            /* [out][in] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumDisplayUnitGroups * This);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumDisplayUnitGroups * This,
            /* [in] */ ULONG celt);
        
        END_INTERFACE
    } IEnumDisplayUnitGroupsVtbl;

    interface IEnumDisplayUnitGroups
    {
        CONST_VTBL struct IEnumDisplayUnitGroupsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumDisplayUnitGroups_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumDisplayUnitGroups_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumDisplayUnitGroups_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumDisplayUnitGroups_Clone(This,enumUnits)	\
    ( (This)->lpVtbl -> Clone(This,enumUnits) ) 

#define IEnumDisplayUnitGroups_Next(This,celt,rgelt,pceltFetched)	\
    ( (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched) ) 

#define IEnumDisplayUnitGroups_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumDisplayUnitGroups_Skip(This,celt)	\
    ( (This)->lpVtbl -> Skip(This,celt) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumDisplayUnitGroups_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitMgr_INTERFACE_DEFINED__
#define __IDisplayUnitMgr_INTERFACE_DEFINED__

/* interface IDisplayUnitMgr */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDisplayUnitMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51F0A2A9-CAC1-11D3-8CE1-A85CC0A0E770")
    IDisplayUnitMgr : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR bstrGroup,
            /* [retval][out] */ IDisplayUnitGroup **group) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrGroup,
            /* [in] */ BSTR bstrUnitType,
            /* [retval][out] */ IDisplayUnitGroup **newGroup) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            BSTR bstrGroup) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Format( 
            /* [in] */ Float64 val,
            /* [in] */ BSTR group,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString) = 0;
        
        virtual /* [helpstring][helpcontext][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumDisplayUnitGroups( 
            /* [retval][out] */ IEnumDisplayUnitGroups **enumDisplayUnitGroups) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [in] */ BSTR group,
            /* [retval][out] */ BSTR *tag) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertToDisplayUnits( 
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertFromDisplayUnits( 
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitMgr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitMgr * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDisplayUnitMgr * This,
            /* [in] */ BSTR bstrGroup,
            /* [retval][out] */ IDisplayUnitGroup **group);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDisplayUnitMgr * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDisplayUnitMgr * This,
            /* [retval][out] */ CollectionIndexType *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDisplayUnitMgr * This,
            /* [in] */ BSTR bstrGroup,
            /* [in] */ BSTR bstrUnitType,
            /* [retval][out] */ IDisplayUnitGroup **newGroup);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDisplayUnitMgr * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDisplayUnitMgr * This,
            BSTR bstrGroup);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IDisplayUnitMgr * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR group,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString);
        
        /* [helpstring][helpcontext][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumDisplayUnitGroups )( 
            IDisplayUnitMgr * This,
            /* [retval][out] */ IEnumDisplayUnitGroups **enumDisplayUnitGroups);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tag )( 
            IDisplayUnitMgr * This,
            /* [in] */ BSTR group,
            /* [retval][out] */ BSTR *tag);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertToDisplayUnits )( 
            IDisplayUnitMgr * This,
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromDisplayUnits )( 
            IDisplayUnitMgr * This,
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result);
        
        END_INTERFACE
    } IDisplayUnitMgrVtbl;

    interface IDisplayUnitMgr
    {
        CONST_VTBL struct IDisplayUnitMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitMgr_get_Item(This,bstrGroup,group)	\
    ( (This)->lpVtbl -> get_Item(This,bstrGroup,group) ) 

#define IDisplayUnitMgr_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDisplayUnitMgr_get_Count(This,retval)	\
    ( (This)->lpVtbl -> get_Count(This,retval) ) 

#define IDisplayUnitMgr_Add(This,bstrGroup,bstrUnitType,newGroup)	\
    ( (This)->lpVtbl -> Add(This,bstrGroup,bstrUnitType,newGroup) ) 

#define IDisplayUnitMgr_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDisplayUnitMgr_Remove(This,bstrGroup)	\
    ( (This)->lpVtbl -> Remove(This,bstrGroup) ) 

#define IDisplayUnitMgr_Format(This,val,group,bShowUnitTag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,group,bShowUnitTag,fmtString) ) 

#define IDisplayUnitMgr_get__EnumDisplayUnitGroups(This,enumDisplayUnitGroups)	\
    ( (This)->lpVtbl -> get__EnumDisplayUnitGroups(This,enumDisplayUnitGroups) ) 

#define IDisplayUnitMgr_get_Tag(This,group,tag)	\
    ( (This)->lpVtbl -> get_Tag(This,group,tag) ) 

#define IDisplayUnitMgr_ConvertToDisplayUnits(This,value,group,result)	\
    ( (This)->lpVtbl -> ConvertToDisplayUnits(This,value,group,result) ) 

#define IDisplayUnitMgr_ConvertFromDisplayUnits(This,value,group,result)	\
    ( (This)->lpVtbl -> ConvertFromDisplayUnits(This,value,group,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitMgr_INTERFACE_DEFINED__ */


#ifndef __IUnitModeController_INTERFACE_DEFINED__
#define __IUnitModeController_INTERFACE_DEFINED__

/* interface IUnitModeController */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitModeController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51F0A2A1-CAC1-11D3-8CE1-A85CC0A0E770")
    IUnitModeController : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ UnitModeType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ UnitModeType newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ShowSelectionDialog( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ShowSelectionDialogEx( 
            /* [in] */ BSTR helpFile,
            /* [in] */ long nID) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitModeControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitModeController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitModeController * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitModeController * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            IUnitModeController * This,
            /* [retval][out] */ UnitModeType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            IUnitModeController * This,
            /* [in] */ UnitModeType newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ShowSelectionDialog )( 
            IUnitModeController * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ShowSelectionDialogEx )( 
            IUnitModeController * This,
            /* [in] */ BSTR helpFile,
            /* [in] */ long nID);
        
        END_INTERFACE
    } IUnitModeControllerVtbl;

    interface IUnitModeController
    {
        CONST_VTBL struct IUnitModeControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitModeController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitModeController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitModeController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitModeController_get_UnitMode(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitMode(This,pVal) ) 

#define IUnitModeController_put_UnitMode(This,newVal)	\
    ( (This)->lpVtbl -> put_UnitMode(This,newVal) ) 

#define IUnitModeController_ShowSelectionDialog(This)	\
    ( (This)->lpVtbl -> ShowSelectionDialog(This) ) 

#define IUnitModeController_ShowSelectionDialogEx(This,helpFile,nID)	\
    ( (This)->lpVtbl -> ShowSelectionDialogEx(This,helpFile,nID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitModeController_INTERFACE_DEFINED__ */


#ifndef __IUnitSystem_INTERFACE_DEFINED__
#define __IUnitSystem_INTERFACE_DEFINED__

/* interface IUnitSystem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51F0A2C4-CAC1-11D3-8CE1-A85CC0A0E770")
    IUnitSystem : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitServer( 
            /* [retval][out] */ IUnitServer **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayUnitMgr( 
            /* [retval][out] */ IDisplayUnitMgr **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitModeController( 
            /* [retval][out] */ IUnitModeController **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitSystem * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitServer )( 
            IUnitSystem * This,
            /* [retval][out] */ IUnitServer **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayUnitMgr )( 
            IUnitSystem * This,
            /* [retval][out] */ IDisplayUnitMgr **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitModeController )( 
            IUnitSystem * This,
            /* [retval][out] */ IUnitModeController **pVal);
        
        END_INTERFACE
    } IUnitSystemVtbl;

    interface IUnitSystem
    {
        CONST_VTBL struct IUnitSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitSystem_get_UnitServer(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitServer(This,pVal) ) 

#define IUnitSystem_get_DisplayUnitMgr(This,pVal)	\
    ( (This)->lpVtbl -> get_DisplayUnitMgr(This,pVal) ) 

#define IUnitSystem_get_UnitModeController(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitModeController(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitSystem_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitMgr2_INTERFACE_DEFINED__
#define __IDisplayUnitMgr2_INTERFACE_DEFINED__

/* interface IDisplayUnitMgr2 */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDisplayUnitMgr2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE8269CB-5568-11d4-8CE4-0080C7380027")
    IDisplayUnitMgr2 : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR bstrGroup,
            /* [retval][out] */ IDisplayUnitGroup **group) = 0;
        
        virtual /* [helpstring][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bstrGroup,
            /* [in] */ BSTR bstrUnitType,
            /* [retval][out] */ IDisplayUnitGroup **newGroup) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Remove( 
            BSTR bstrGroup) = 0;
        
        virtual /* [helpstring][helpcontext][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__EnumDisplayUnitGroups( 
            /* [retval][out] */ IEnumDisplayUnitGroups **enumDisplayUnitGroups) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitMgr2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitMgr2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitMgr2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitMgr2 * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IDisplayUnitMgr2 * This,
            /* [in] */ BSTR bstrGroup,
            /* [retval][out] */ IDisplayUnitGroup **group);
        
        /* [helpstring][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IDisplayUnitMgr2 * This,
            /* [retval][out] */ IUnknown **retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IDisplayUnitMgr2 * This,
            /* [retval][out] */ CollectionIndexType *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IDisplayUnitMgr2 * This,
            /* [in] */ BSTR bstrGroup,
            /* [in] */ BSTR bstrUnitType,
            /* [retval][out] */ IDisplayUnitGroup **newGroup);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IDisplayUnitMgr2 * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IDisplayUnitMgr2 * This,
            BSTR bstrGroup);
        
        /* [helpstring][helpcontext][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE *get__EnumDisplayUnitGroups )( 
            IDisplayUnitMgr2 * This,
            /* [retval][out] */ IEnumDisplayUnitGroups **enumDisplayUnitGroups);
        
        END_INTERFACE
    } IDisplayUnitMgr2Vtbl;

    interface IDisplayUnitMgr2
    {
        CONST_VTBL struct IDisplayUnitMgr2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitMgr2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitMgr2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitMgr2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitMgr2_get_Item(This,bstrGroup,group)	\
    ( (This)->lpVtbl -> get_Item(This,bstrGroup,group) ) 

#define IDisplayUnitMgr2_get__NewEnum(This,retval)	\
    ( (This)->lpVtbl -> get__NewEnum(This,retval) ) 

#define IDisplayUnitMgr2_get_Count(This,retval)	\
    ( (This)->lpVtbl -> get_Count(This,retval) ) 

#define IDisplayUnitMgr2_Add(This,bstrGroup,bstrUnitType,newGroup)	\
    ( (This)->lpVtbl -> Add(This,bstrGroup,bstrUnitType,newGroup) ) 

#define IDisplayUnitMgr2_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IDisplayUnitMgr2_Remove(This,bstrGroup)	\
    ( (This)->lpVtbl -> Remove(This,bstrGroup) ) 

#define IDisplayUnitMgr2_get__EnumDisplayUnitGroups(This,enumDisplayUnitGroups)	\
    ( (This)->lpVtbl -> get__EnumDisplayUnitGroups(This,enumDisplayUnitGroups) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitMgr2_INTERFACE_DEFINED__ */


#ifndef __IAppUnitSystem_INTERFACE_DEFINED__
#define __IAppUnitSystem_INTERFACE_DEFINED__

/* interface IAppUnitSystem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IAppUnitSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16683EE1-558C-11D4-8CE4-0080C7380027")
    IAppUnitSystem : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertToBaseUnits( 
            /* [in] */ Float64 value,
            /* [in] */ VARIANT fromUnit,
            /* [retval][out] */ Float64 *retval) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertFromBaseUnits( 
            /* [in] */ Float64 value,
            /* [in] */ VARIANT toUnit,
            /* [retval][out] */ Float64 *retval) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitServer( 
            /* [retval][out] */ IUnitServer **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayUnitMgr( 
            /* [retval][out] */ IDisplayUnitMgr2 **pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAppUnitSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAppUnitSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAppUnitSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAppUnitSystem * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertToBaseUnits )( 
            IAppUnitSystem * This,
            /* [in] */ Float64 value,
            /* [in] */ VARIANT fromUnit,
            /* [retval][out] */ Float64 *retval);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromBaseUnits )( 
            IAppUnitSystem * This,
            /* [in] */ Float64 value,
            /* [in] */ VARIANT toUnit,
            /* [retval][out] */ Float64 *retval);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitServer )( 
            IAppUnitSystem * This,
            /* [retval][out] */ IUnitServer **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayUnitMgr )( 
            IAppUnitSystem * This,
            /* [retval][out] */ IDisplayUnitMgr2 **pVal);
        
        END_INTERFACE
    } IAppUnitSystemVtbl;

    interface IAppUnitSystem
    {
        CONST_VTBL struct IAppUnitSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAppUnitSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAppUnitSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAppUnitSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAppUnitSystem_ConvertToBaseUnits(This,value,fromUnit,retval)	\
    ( (This)->lpVtbl -> ConvertToBaseUnits(This,value,fromUnit,retval) ) 

#define IAppUnitSystem_ConvertFromBaseUnits(This,value,toUnit,retval)	\
    ( (This)->lpVtbl -> ConvertFromBaseUnits(This,value,toUnit,retval) ) 

#define IAppUnitSystem_get_UnitServer(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitServer(This,pVal) ) 

#define IAppUnitSystem_get_DisplayUnitMgr(This,pVal)	\
    ( (This)->lpVtbl -> get_DisplayUnitMgr(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAppUnitSystem_INTERFACE_DEFINED__ */


#ifndef __IDocUnitSystem_INTERFACE_DEFINED__
#define __IDocUnitSystem_INTERFACE_DEFINED__

/* interface IDocUnitSystem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IDocUnitSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("16683EE5-558C-11D4-8CE4-0080C7380027")
    IDocUnitSystem : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitMode( 
            /* [retval][out] */ UnitModeType *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propput] */ HRESULT STDMETHODCALLTYPE put_UnitMode( 
            /* [in] */ UnitModeType newVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitModeController( 
            /* [retval][out] */ IUnitModeController **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_AppUnitSystem( 
            /* [retval][out] */ IAppUnitSystem **pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_AppUnitSystem( 
            /* [in] */ IAppUnitSystem *newVal) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertToDisplayUnits( 
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ConvertFromDisplayUnits( 
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [in] */ BSTR group,
            /* [retval][out] */ BSTR *tag) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Format( 
            /* [in] */ Float64 val,
            /* [in] */ BSTR group,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDocUnitSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDocUnitSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDocUnitSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDocUnitSystem * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitMode )( 
            IDocUnitSystem * This,
            /* [retval][out] */ UnitModeType *pVal);
        
        /* [helpstring][helpcontext][propput] */ HRESULT ( STDMETHODCALLTYPE *put_UnitMode )( 
            IDocUnitSystem * This,
            /* [in] */ UnitModeType newVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitModeController )( 
            IDocUnitSystem * This,
            /* [retval][out] */ IUnitModeController **pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AppUnitSystem )( 
            IDocUnitSystem * This,
            /* [retval][out] */ IAppUnitSystem **pVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_AppUnitSystem )( 
            IDocUnitSystem * This,
            /* [in] */ IAppUnitSystem *newVal);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertToDisplayUnits )( 
            IDocUnitSystem * This,
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *ConvertFromDisplayUnits )( 
            IDocUnitSystem * This,
            /* [in] */ Float64 value,
            /* [in] */ BSTR group,
            /* [retval][out] */ Float64 *result);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Tag )( 
            IDocUnitSystem * This,
            /* [in] */ BSTR group,
            /* [retval][out] */ BSTR *tag);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *Format )( 
            IDocUnitSystem * This,
            /* [in] */ Float64 val,
            /* [in] */ BSTR group,
            /* [in] */ VARIANT_BOOL bShowUnitTag,
            /* [retval][out] */ BSTR *fmtString);
        
        END_INTERFACE
    } IDocUnitSystemVtbl;

    interface IDocUnitSystem
    {
        CONST_VTBL struct IDocUnitSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDocUnitSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDocUnitSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDocUnitSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDocUnitSystem_get_UnitMode(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitMode(This,pVal) ) 

#define IDocUnitSystem_put_UnitMode(This,newVal)	\
    ( (This)->lpVtbl -> put_UnitMode(This,newVal) ) 

#define IDocUnitSystem_get_UnitModeController(This,pVal)	\
    ( (This)->lpVtbl -> get_UnitModeController(This,pVal) ) 

#define IDocUnitSystem_get_AppUnitSystem(This,pVal)	\
    ( (This)->lpVtbl -> get_AppUnitSystem(This,pVal) ) 

#define IDocUnitSystem_putref_AppUnitSystem(This,newVal)	\
    ( (This)->lpVtbl -> putref_AppUnitSystem(This,newVal) ) 

#define IDocUnitSystem_ConvertToDisplayUnits(This,value,group,result)	\
    ( (This)->lpVtbl -> ConvertToDisplayUnits(This,value,group,result) ) 

#define IDocUnitSystem_ConvertFromDisplayUnits(This,value,group,result)	\
    ( (This)->lpVtbl -> ConvertFromDisplayUnits(This,value,group,result) ) 

#define IDocUnitSystem_get_Tag(This,group,tag)	\
    ( (This)->lpVtbl -> get_Tag(This,group,tag) ) 

#define IDocUnitSystem_Format(This,val,group,bShowUnitTag,fmtString)	\
    ( (This)->lpVtbl -> Format(This,val,group,bShowUnitTag,fmtString) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDocUnitSystem_INTERFACE_DEFINED__ */


#ifndef __ISupportUnitServer_INTERFACE_DEFINED__
#define __ISupportUnitServer_INTERFACE_DEFINED__

/* interface ISupportUnitServer */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportUnitServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6813130-1D7F-11d2-8EAC-006097DF3C68")
    ISupportUnitServer : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitServer( 
            /* [retval][out] */ IUnitServer **ppVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_UnitServer( 
            /* [in] */ IUnitServer *pNewVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportUnitServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportUnitServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportUnitServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportUnitServer * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitServer )( 
            ISupportUnitServer * This,
            /* [retval][out] */ IUnitServer **ppVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_UnitServer )( 
            ISupportUnitServer * This,
            /* [in] */ IUnitServer *pNewVal);
        
        END_INTERFACE
    } ISupportUnitServerVtbl;

    interface ISupportUnitServer
    {
        CONST_VTBL struct ISupportUnitServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportUnitServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportUnitServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportUnitServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportUnitServer_get_UnitServer(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnitServer(This,ppVal) ) 

#define ISupportUnitServer_putref_UnitServer(This,pNewVal)	\
    ( (This)->lpVtbl -> putref_UnitServer(This,pNewVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportUnitServer_INTERFACE_DEFINED__ */


#ifndef __ISupportUnitSystem_INTERFACE_DEFINED__
#define __ISupportUnitSystem_INTERFACE_DEFINED__

/* interface ISupportUnitSystem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportUnitSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FDA8EDC3-E3FE-11d3-8A3F-006097C68A9C")
    ISupportUnitSystem : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitSystem( 
            /* [retval][out] */ IUnitSystem **ppVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_UnitSystem( 
            /* [in] */ IUnitSystem *pNewVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportUnitSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportUnitSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportUnitSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportUnitSystem * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitSystem )( 
            ISupportUnitSystem * This,
            /* [retval][out] */ IUnitSystem **ppVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_UnitSystem )( 
            ISupportUnitSystem * This,
            /* [in] */ IUnitSystem *pNewVal);
        
        END_INTERFACE
    } ISupportUnitSystemVtbl;

    interface ISupportUnitSystem
    {
        CONST_VTBL struct ISupportUnitSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportUnitSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportUnitSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportUnitSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportUnitSystem_get_UnitSystem(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnitSystem(This,ppVal) ) 

#define ISupportUnitSystem_putref_UnitSystem(This,pNewVal)	\
    ( (This)->lpVtbl -> putref_UnitSystem(This,pNewVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportUnitSystem_INTERFACE_DEFINED__ */


#ifndef __ISupportDisplayUnits_INTERFACE_DEFINED__
#define __ISupportDisplayUnits_INTERFACE_DEFINED__

/* interface ISupportDisplayUnits */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportDisplayUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("24A18718-E49F-11d3-8A40-006097C68A9C")
    ISupportDisplayUnits : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayUnitMgr( 
            /* [retval][out] */ IDisplayUnitMgr **ppVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_DisplayUnitMgr( 
            /* [in] */ IDisplayUnitMgr *pNewVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportDisplayUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportDisplayUnits * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportDisplayUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportDisplayUnits * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DisplayUnitMgr )( 
            ISupportDisplayUnits * This,
            /* [retval][out] */ IDisplayUnitMgr **ppVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_DisplayUnitMgr )( 
            ISupportDisplayUnits * This,
            /* [in] */ IDisplayUnitMgr *pNewVal);
        
        END_INTERFACE
    } ISupportDisplayUnitsVtbl;

    interface ISupportDisplayUnits
    {
        CONST_VTBL struct ISupportDisplayUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportDisplayUnits_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportDisplayUnits_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportDisplayUnits_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportDisplayUnits_get_DisplayUnitMgr(This,ppVal)	\
    ( (This)->lpVtbl -> get_DisplayUnitMgr(This,ppVal) ) 

#define ISupportDisplayUnits_putref_DisplayUnitMgr(This,pNewVal)	\
    ( (This)->lpVtbl -> putref_DisplayUnitMgr(This,pNewVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportDisplayUnits_INTERFACE_DEFINED__ */


#ifndef __ISupportDocUnitSystem_INTERFACE_DEFINED__
#define __ISupportDocUnitSystem_INTERFACE_DEFINED__

/* interface ISupportDocUnitSystem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISupportDocUnitSystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7E9EAC0-5764-11d4-8CE4-0080C7380027")
    ISupportDocUnitSystem : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_UnitSystem( 
            /* [retval][out] */ IDocUnitSystem **ppVal) = 0;
        
        virtual /* [helpstring][helpcontext][propputref] */ HRESULT STDMETHODCALLTYPE putref_UnitSystem( 
            /* [in] */ IDocUnitSystem *pNewVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISupportDocUnitSystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupportDocUnitSystem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupportDocUnitSystem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupportDocUnitSystem * This);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE *get_UnitSystem )( 
            ISupportDocUnitSystem * This,
            /* [retval][out] */ IDocUnitSystem **ppVal);
        
        /* [helpstring][helpcontext][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_UnitSystem )( 
            ISupportDocUnitSystem * This,
            /* [in] */ IDocUnitSystem *pNewVal);
        
        END_INTERFACE
    } ISupportDocUnitSystemVtbl;

    interface ISupportDocUnitSystem
    {
        CONST_VTBL struct ISupportDocUnitSystemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupportDocUnitSystem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupportDocUnitSystem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupportDocUnitSystem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupportDocUnitSystem_get_UnitSystem(This,ppVal)	\
    ( (This)->lpVtbl -> get_UnitSystem(This,ppVal) ) 

#define ISupportDocUnitSystem_putref_UnitSystem(This,pNewVal)	\
    ( (This)->lpVtbl -> putref_UnitSystem(This,pNewVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupportDocUnitSystem_INTERFACE_DEFINED__ */


#ifndef __IUnitServerEventSink_INTERFACE_DEFINED__
#define __IUnitServerEventSink_INTERFACE_DEFINED__

/* interface IUnitServerEventSink */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IUnitServerEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2531DFCA-5873-4d25-8639-4414FBFD1997")
    IUnitServerEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitAdded( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitRemoved( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitsCleared( 
            /* [in] */ IUnitType *unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypeAdded( 
            /* [in] */ IUnitType *unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypeRemoved( 
            /* [in] */ BSTR unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitServerEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitServerEventSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitServerEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitServerEventSink * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitAdded )( 
            IUnitServerEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitRemoved )( 
            IUnitServerEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitsCleared )( 
            IUnitServerEventSink * This,
            /* [in] */ IUnitType *unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypeAdded )( 
            IUnitServerEventSink * This,
            /* [in] */ IUnitType *unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypeRemoved )( 
            IUnitServerEventSink * This,
            /* [in] */ BSTR unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypesCleared )( 
            IUnitServerEventSink * This);
        
        END_INTERFACE
    } IUnitServerEventSinkVtbl;

    interface IUnitServerEventSink
    {
        CONST_VTBL struct IUnitServerEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitServerEventSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitServerEventSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitServerEventSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitServerEventSink_OnUnitAdded(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitAdded(This,unitType,unit) ) 

#define IUnitServerEventSink_OnUnitRemoved(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitRemoved(This,unitType,unit) ) 

#define IUnitServerEventSink_OnUnitsCleared(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitsCleared(This,unitType) ) 

#define IUnitServerEventSink_OnUnitTypeAdded(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitTypeAdded(This,unitType) ) 

#define IUnitServerEventSink_OnUnitTypeRemoved(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitTypeRemoved(This,unitType) ) 

#define IUnitServerEventSink_OnUnitTypesCleared(This)	\
    ( (This)->lpVtbl -> OnUnitTypesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitServerEventSink_INTERFACE_DEFINED__ */


#ifndef __IUnitsEventSink_INTERFACE_DEFINED__
#define __IUnitsEventSink_INTERFACE_DEFINED__

/* interface IUnitsEventSink */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IUnitsEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51A2D507-7A88-4103-80CC-708BDC662510")
    IUnitsEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitAdded( 
            /* [in] */ IUnit *unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitRemoved( 
            /* [in] */ BSTR unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitsEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitsEventSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitsEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitsEventSink * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitAdded )( 
            IUnitsEventSink * This,
            /* [in] */ IUnit *unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitRemoved )( 
            IUnitsEventSink * This,
            /* [in] */ BSTR unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitsCleared )( 
            IUnitsEventSink * This);
        
        END_INTERFACE
    } IUnitsEventSinkVtbl;

    interface IUnitsEventSink
    {
        CONST_VTBL struct IUnitsEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitsEventSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitsEventSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitsEventSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitsEventSink_OnUnitAdded(This,unit)	\
    ( (This)->lpVtbl -> OnUnitAdded(This,unit) ) 

#define IUnitsEventSink_OnUnitRemoved(This,unit)	\
    ( (This)->lpVtbl -> OnUnitRemoved(This,unit) ) 

#define IUnitsEventSink_OnUnitsCleared(This)	\
    ( (This)->lpVtbl -> OnUnitsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitsEventSink_INTERFACE_DEFINED__ */


#ifndef __IUnitTypeEventSink_INTERFACE_DEFINED__
#define __IUnitTypeEventSink_INTERFACE_DEFINED__

/* interface IUnitTypeEventSink */
/* [unique][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitTypeEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45D053AD-7893-4eb1-895B-750406204F84")
    IUnitTypeEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitAdded( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitRemoved( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitsCleared( 
            /* [in] */ IUnitType *unitType) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitTypeEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitTypeEventSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitTypeEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitTypeEventSink * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitAdded )( 
            IUnitTypeEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitRemoved )( 
            IUnitTypeEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitsCleared )( 
            IUnitTypeEventSink * This,
            /* [in] */ IUnitType *unitType);
        
        END_INTERFACE
    } IUnitTypeEventSinkVtbl;

    interface IUnitTypeEventSink
    {
        CONST_VTBL struct IUnitTypeEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitTypeEventSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitTypeEventSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitTypeEventSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitTypeEventSink_OnUnitAdded(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitAdded(This,unitType,unit) ) 

#define IUnitTypeEventSink_OnUnitRemoved(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitRemoved(This,unitType,unit) ) 

#define IUnitTypeEventSink_OnUnitsCleared(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitsCleared(This,unitType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitTypeEventSink_INTERFACE_DEFINED__ */


#ifndef __IUnitTypesEventSink_INTERFACE_DEFINED__
#define __IUnitTypesEventSink_INTERFACE_DEFINED__

/* interface IUnitTypesEventSink */
/* [unique][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IUnitTypesEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A5CEF04-07AA-4285-B2A0-3A5452073762")
    IUnitTypesEventSink : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitAdded( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitRemoved( 
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitsCleared( 
            /* [in] */ IUnitType *unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypeAdded( 
            /* [in] */ IUnitType *unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypeRemoved( 
            /* [in] */ BSTR unitType) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitTypesCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitTypesEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitTypesEventSink * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitTypesEventSink * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitTypesEventSink * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitAdded )( 
            IUnitTypesEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ IUnit *unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitRemoved )( 
            IUnitTypesEventSink * This,
            /* [in] */ IUnitType *unitType,
            /* [in] */ BSTR unit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitsCleared )( 
            IUnitTypesEventSink * This,
            /* [in] */ IUnitType *unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypeAdded )( 
            IUnitTypesEventSink * This,
            /* [in] */ IUnitType *unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypeRemoved )( 
            IUnitTypesEventSink * This,
            /* [in] */ BSTR unitType);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitTypesCleared )( 
            IUnitTypesEventSink * This);
        
        END_INTERFACE
    } IUnitTypesEventSinkVtbl;

    interface IUnitTypesEventSink
    {
        CONST_VTBL struct IUnitTypesEventSinkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitTypesEventSink_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitTypesEventSink_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitTypesEventSink_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitTypesEventSink_OnUnitAdded(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitAdded(This,unitType,unit) ) 

#define IUnitTypesEventSink_OnUnitRemoved(This,unitType,unit)	\
    ( (This)->lpVtbl -> OnUnitRemoved(This,unitType,unit) ) 

#define IUnitTypesEventSink_OnUnitsCleared(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitsCleared(This,unitType) ) 

#define IUnitTypesEventSink_OnUnitTypeAdded(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitTypeAdded(This,unitType) ) 

#define IUnitTypesEventSink_OnUnitTypeRemoved(This,unitType)	\
    ( (This)->lpVtbl -> OnUnitTypeRemoved(This,unitType) ) 

#define IUnitTypesEventSink_OnUnitTypesCleared(This)	\
    ( (This)->lpVtbl -> OnUnitTypesCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitTypesEventSink_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitEvents_INTERFACE_DEFINED__
#define __IDisplayUnitEvents_INTERFACE_DEFINED__

/* interface IDisplayUnitEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDisplayUnitEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64A00B5C-FBDA-4bcd-9F22-472C48D0E73D")
    IDisplayUnitEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnFormatChanged( 
            /* [in] */ IDisplayUnit *displayUnit) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnFormatChanged )( 
            IDisplayUnitEvents * This,
            /* [in] */ IDisplayUnit *displayUnit);
        
        END_INTERFACE
    } IDisplayUnitEventsVtbl;

    interface IDisplayUnitEvents
    {
        CONST_VTBL struct IDisplayUnitEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitEvents_OnFormatChanged(This,displayUnit)	\
    ( (This)->lpVtbl -> OnFormatChanged(This,displayUnit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitEvents_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitGroupEvents_INTERFACE_DEFINED__
#define __IDisplayUnitGroupEvents_INTERFACE_DEFINED__

/* interface IDisplayUnitGroupEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDisplayUnitGroupEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DCAA5CAB-2DB4-41c5-B946-FC3E93FEE423")
    IDisplayUnitGroupEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnFormatChanged( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitCreated( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitRemoved( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ BSTR displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitGroupCleared( 
            /* [in] */ IDisplayUnitGroup *group) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitGroupEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitGroupEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitGroupEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitGroupEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnFormatChanged )( 
            IDisplayUnitGroupEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitCreated )( 
            IDisplayUnitGroupEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitRemoved )( 
            IDisplayUnitGroupEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ BSTR displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitGroupCleared )( 
            IDisplayUnitGroupEvents * This,
            /* [in] */ IDisplayUnitGroup *group);
        
        END_INTERFACE
    } IDisplayUnitGroupEventsVtbl;

    interface IDisplayUnitGroupEvents
    {
        CONST_VTBL struct IDisplayUnitGroupEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitGroupEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitGroupEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitGroupEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitGroupEvents_OnFormatChanged(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnFormatChanged(This,group,displayUnit) ) 

#define IDisplayUnitGroupEvents_OnDisplayUnitCreated(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnDisplayUnitCreated(This,group,displayUnit) ) 

#define IDisplayUnitGroupEvents_OnDisplayUnitRemoved(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnDisplayUnitRemoved(This,group,displayUnit) ) 

#define IDisplayUnitGroupEvents_OnDisplayUnitGroupCleared(This,group)	\
    ( (This)->lpVtbl -> OnDisplayUnitGroupCleared(This,group) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitGroupEvents_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitMgrEvents_INTERFACE_DEFINED__
#define __IDisplayUnitMgrEvents_INTERFACE_DEFINED__

/* interface IDisplayUnitMgrEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDisplayUnitMgrEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43581ACD-6397-404a-A9FA-0D79922A22C4")
    IDisplayUnitMgrEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnFormatChanged( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitCreated( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitRemoved( 
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ BSTR displayUnit) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitGroupCleared( 
            /* [in] */ IDisplayUnitGroup *group) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitGroupCreated( 
            /* [in] */ IDisplayUnitGroup *group) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitGroupRemoved( 
            /* [in] */ BSTR group) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnDisplayUnitGroupsCleared( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitMgrEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitMgrEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitMgrEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnFormatChanged )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitCreated )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ IDisplayUnit *displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitRemoved )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ IDisplayUnitGroup *group,
            /* [in] */ BSTR displayUnit);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitGroupCleared )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ IDisplayUnitGroup *group);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitGroupCreated )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ IDisplayUnitGroup *group);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitGroupRemoved )( 
            IDisplayUnitMgrEvents * This,
            /* [in] */ BSTR group);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnDisplayUnitGroupsCleared )( 
            IDisplayUnitMgrEvents * This);
        
        END_INTERFACE
    } IDisplayUnitMgrEventsVtbl;

    interface IDisplayUnitMgrEvents
    {
        CONST_VTBL struct IDisplayUnitMgrEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitMgrEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitMgrEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitMgrEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitMgrEvents_OnFormatChanged(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnFormatChanged(This,group,displayUnit) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitCreated(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnDisplayUnitCreated(This,group,displayUnit) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitRemoved(This,group,displayUnit)	\
    ( (This)->lpVtbl -> OnDisplayUnitRemoved(This,group,displayUnit) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitGroupCleared(This,group)	\
    ( (This)->lpVtbl -> OnDisplayUnitGroupCleared(This,group) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitGroupCreated(This,group)	\
    ( (This)->lpVtbl -> OnDisplayUnitGroupCreated(This,group) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitGroupRemoved(This,group)	\
    ( (This)->lpVtbl -> OnDisplayUnitGroupRemoved(This,group) ) 

#define IDisplayUnitMgrEvents_OnDisplayUnitGroupsCleared(This)	\
    ( (This)->lpVtbl -> OnDisplayUnitGroupsCleared(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitMgrEvents_INTERFACE_DEFINED__ */


#ifndef __IUnitSystemEvents_INTERFACE_DEFINED__
#define __IUnitSystemEvents_INTERFACE_DEFINED__

/* interface IUnitSystemEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IUnitSystemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8D8BE756-EA66-4963-8FAC-935DCC57F434")
    IUnitSystemEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUpdateDisplay( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitServerChanged( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitSystemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitSystemEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitSystemEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitSystemEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUpdateDisplay )( 
            IUnitSystemEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitServerChanged )( 
            IUnitSystemEvents * This);
        
        END_INTERFACE
    } IUnitSystemEventsVtbl;

    interface IUnitSystemEvents
    {
        CONST_VTBL struct IUnitSystemEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitSystemEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitSystemEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitSystemEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitSystemEvents_OnUpdateDisplay(This)	\
    ( (This)->lpVtbl -> OnUpdateDisplay(This) ) 

#define IUnitSystemEvents_OnUnitServerChanged(This)	\
    ( (This)->lpVtbl -> OnUnitServerChanged(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitSystemEvents_INTERFACE_DEFINED__ */


#ifndef __IUnitModeControllerEvents_INTERFACE_DEFINED__
#define __IUnitModeControllerEvents_INTERFACE_DEFINED__

/* interface IUnitModeControllerEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IUnitModeControllerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F71412A3-A63B-4f5b-8A02-9E263090F914")
    IUnitModeControllerEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUnitModeChanged( 
            /* [in] */ UnitModeType newMode) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitModeControllerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitModeControllerEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitModeControllerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitModeControllerEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUnitModeChanged )( 
            IUnitModeControllerEvents * This,
            /* [in] */ UnitModeType newMode);
        
        END_INTERFACE
    } IUnitModeControllerEventsVtbl;

    interface IUnitModeControllerEvents
    {
        CONST_VTBL struct IUnitModeControllerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitModeControllerEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitModeControllerEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitModeControllerEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitModeControllerEvents_OnUnitModeChanged(This,newMode)	\
    ( (This)->lpVtbl -> OnUnitModeChanged(This,newMode) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitModeControllerEvents_INTERFACE_DEFINED__ */


#ifndef __IDisplayUnitFormatterEvents_INTERFACE_DEFINED__
#define __IDisplayUnitFormatterEvents_INTERFACE_DEFINED__

/* interface IDisplayUnitFormatterEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDisplayUnitFormatterEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("15AE8080-0171-4687-86DB-CD95393202FB")
    IDisplayUnitFormatterEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnFormatChanged( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDisplayUnitFormatterEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDisplayUnitFormatterEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDisplayUnitFormatterEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDisplayUnitFormatterEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnFormatChanged )( 
            IDisplayUnitFormatterEvents * This);
        
        END_INTERFACE
    } IDisplayUnitFormatterEventsVtbl;

    interface IDisplayUnitFormatterEvents
    {
        CONST_VTBL struct IDisplayUnitFormatterEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDisplayUnitFormatterEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDisplayUnitFormatterEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDisplayUnitFormatterEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDisplayUnitFormatterEvents_OnFormatChanged(This)	\
    ( (This)->lpVtbl -> OnFormatChanged(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDisplayUnitFormatterEvents_INTERFACE_DEFINED__ */


#ifndef __IDocUnitSystemEvents_INTERFACE_DEFINED__
#define __IDocUnitSystemEvents_INTERFACE_DEFINED__

/* interface IDocUnitSystemEvents */
/* [unique][uuid][oleautomation][object] */ 


EXTERN_C const IID IID_IDocUnitSystemEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7C8079B-87E8-4c37-9F31-073A388B5484")
    IDocUnitSystemEvents : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE OnUpdateDisplay( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDocUnitSystemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDocUnitSystemEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDocUnitSystemEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDocUnitSystemEvents * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE *OnUpdateDisplay )( 
            IDocUnitSystemEvents * This);
        
        END_INTERFACE
    } IDocUnitSystemEventsVtbl;

    interface IDocUnitSystemEvents
    {
        CONST_VTBL struct IDocUnitSystemEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDocUnitSystemEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDocUnitSystemEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDocUnitSystemEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDocUnitSystemEvents_OnUpdateDisplay(This)	\
    ( (This)->lpVtbl -> OnUpdateDisplay(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDocUnitSystemEvents_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DocUnitSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("16683EE6-558C-11D4-8CE4-0080C7380027")
DocUnitSystem;
#endif

EXTERN_C const CLSID CLSID_DisplayUnitMgr2;

#ifdef __cplusplus

class DECLSPEC_UUID("CE8269CC-5568-11d4-8CE4-0080C7380027")
DisplayUnitMgr2;
#endif

EXTERN_C const CLSID CLSID_AppUnitSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("16683EE2-558C-11D4-8CE4-0080C7380027")
AppUnitSystem;
#endif

EXTERN_C const CLSID CLSID_UnitServer;

#ifdef __cplusplus

class DECLSPEC_UUID("C65F03C4-16AB-11D2-8D11-94FA07C10000")
UnitServer;
#endif

EXTERN_C const CLSID CLSID_UnitModeController;

#ifdef __cplusplus

class DECLSPEC_UUID("51F0A2A2-CAC1-11D3-8CE1-A85CC0A0E770")
UnitModeController;
#endif

EXTERN_C const CLSID CLSID_DisplayUnitFormatter;

#ifdef __cplusplus

class DECLSPEC_UUID("51F0A2BD-CAC1-11D3-8CE1-A85CC0A0E770")
DisplayUnitFormatter;
#endif

EXTERN_C const CLSID CLSID_AnnotatedDisplayUnitFormatter;

#ifdef __cplusplus

class DECLSPEC_UUID("51F0A2BF-CAC1-11D3-8CE1-A85CC0A0E770")
AnnotatedDisplayUnitFormatter;
#endif

EXTERN_C const CLSID CLSID_UnitSystem;

#ifdef __cplusplus

class DECLSPEC_UUID("51F0A2C5-CAC1-11D3-8CE1-A85CC0A0E770")
UnitSystem;
#endif

EXTERN_C const CLSID CLSID_DisplayUnitMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("DAC8CE20-D36F-11d3-8CE1-A4260772F04A")
DisplayUnitMgr;
#endif

EXTERN_C const CLSID CLSID_Unit;

#ifdef __cplusplus

class DECLSPEC_UUID("47D62466-C499-11d4-8B5B-006097C68A9C")
Unit;
#endif

EXTERN_C const CLSID CLSID_Units;

#ifdef __cplusplus

class DECLSPEC_UUID("47D62468-C499-11d4-8B5B-006097C68A9C")
Units;
#endif

EXTERN_C const CLSID CLSID_UnitType;

#ifdef __cplusplus

class DECLSPEC_UUID("47D62469-C499-11d4-8B5B-006097C68A9C")
UnitType;
#endif

EXTERN_C const CLSID CLSID_UnitTypes;

#ifdef __cplusplus

class DECLSPEC_UUID("47D6246A-C499-11d4-8B5B-006097C68A9C")
UnitTypes;
#endif

EXTERN_C const CLSID CLSID_DisplayUnit;

#ifdef __cplusplus

class DECLSPEC_UUID("47D6246B-C499-11d4-8B5B-006097C68A9C")
DisplayUnit;
#endif

EXTERN_C const CLSID CLSID_DisplayUnitGroup;

#ifdef __cplusplus

class DECLSPEC_UUID("47D6246C-C499-11d4-8B5B-006097C68A9C")
DisplayUnitGroup;
#endif
#endif /* __WBFLUnitServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


