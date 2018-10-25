

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:32:17 2017
 */
/* Compiler settings for ..\Include\WBFLSections.idl:
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


#ifndef __WBFLSections_h__
#define __WBFLSections_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IElasticProperties_FWD_DEFINED__
#define __IElasticProperties_FWD_DEFINED__
typedef interface IElasticProperties IElasticProperties;

#endif 	/* __IElasticProperties_FWD_DEFINED__ */


#ifndef __IMassProperties_FWD_DEFINED__
#define __IMassProperties_FWD_DEFINED__
typedef interface IMassProperties IMassProperties;

#endif 	/* __IMassProperties_FWD_DEFINED__ */


#ifndef __ISection_FWD_DEFINED__
#define __ISection_FWD_DEFINED__
typedef interface ISection ISection;

#endif 	/* __ISection_FWD_DEFINED__ */


#ifndef __ICompositeSectionItem_FWD_DEFINED__
#define __ICompositeSectionItem_FWD_DEFINED__
typedef interface ICompositeSectionItem ICompositeSectionItem;

#endif 	/* __ICompositeSectionItem_FWD_DEFINED__ */


#ifndef __ICompositeSection_FWD_DEFINED__
#define __ICompositeSection_FWD_DEFINED__
typedef interface ICompositeSection ICompositeSection;

#endif 	/* __ICompositeSection_FWD_DEFINED__ */


#ifndef __ICompositeBeam_FWD_DEFINED__
#define __ICompositeBeam_FWD_DEFINED__
typedef interface ICompositeBeam ICompositeBeam;

#endif 	/* __ICompositeBeam_FWD_DEFINED__ */


#ifndef __ICompositeSectionItemEx_FWD_DEFINED__
#define __ICompositeSectionItemEx_FWD_DEFINED__
typedef interface ICompositeSectionItemEx ICompositeSectionItemEx;

#endif 	/* __ICompositeSectionItemEx_FWD_DEFINED__ */


#ifndef __ICompositeSectionEx_FWD_DEFINED__
#define __ICompositeSectionEx_FWD_DEFINED__
typedef interface ICompositeSectionEx ICompositeSectionEx;

#endif 	/* __ICompositeSectionEx_FWD_DEFINED__ */


#ifndef __ElasticProperties_FWD_DEFINED__
#define __ElasticProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class ElasticProperties ElasticProperties;
#else
typedef struct ElasticProperties ElasticProperties;
#endif /* __cplusplus */

#endif 	/* __ElasticProperties_FWD_DEFINED__ */


#ifndef __MassProperties_FWD_DEFINED__
#define __MassProperties_FWD_DEFINED__

#ifdef __cplusplus
typedef class MassProperties MassProperties;
#else
typedef struct MassProperties MassProperties;
#endif /* __cplusplus */

#endif 	/* __MassProperties_FWD_DEFINED__ */


#ifndef __CompositeSectionItem_FWD_DEFINED__
#define __CompositeSectionItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeSectionItem CompositeSectionItem;
#else
typedef struct CompositeSectionItem CompositeSectionItem;
#endif /* __cplusplus */

#endif 	/* __CompositeSectionItem_FWD_DEFINED__ */


#ifndef __CompositeSection_FWD_DEFINED__
#define __CompositeSection_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeSection CompositeSection;
#else
typedef struct CompositeSection CompositeSection;
#endif /* __cplusplus */

#endif 	/* __CompositeSection_FWD_DEFINED__ */


#ifndef __CompositeBeam_FWD_DEFINED__
#define __CompositeBeam_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeBeam CompositeBeam;
#else
typedef struct CompositeBeam CompositeBeam;
#endif /* __cplusplus */

#endif 	/* __CompositeBeam_FWD_DEFINED__ */


#ifndef __CompositeSectionItemEx_FWD_DEFINED__
#define __CompositeSectionItemEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeSectionItemEx CompositeSectionItemEx;
#else
typedef struct CompositeSectionItemEx CompositeSectionItemEx;
#endif /* __cplusplus */

#endif 	/* __CompositeSectionItemEx_FWD_DEFINED__ */


#ifndef __CompositeSectionEx_FWD_DEFINED__
#define __CompositeSectionEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompositeSectionEx CompositeSectionEx;
#else
typedef struct CompositeSectionEx CompositeSectionEx;
#endif /* __cplusplus */

#endif 	/* __CompositeSectionEx_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"
#include "WBFLTools.h"
#include "WBFLGeometry.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WBFLSections_LIBRARY_DEFINED__
#define __WBFLSections_LIBRARY_DEFINED__

/* library WBFLSections */
/* [helpcontext][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WBFLSections;

#ifndef __IElasticProperties_INTERFACE_DEFINED__
#define __IElasticProperties_INTERFACE_DEFINED__

/* interface IElasticProperties */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IElasticProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("866B0CBE-62C2-40D5-B12F-1168F7AF1C55")
    IElasticProperties : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EA( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EA( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Centroid( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Centroid( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EI11( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EI22( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EI12Max( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EI12Min( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EIxx( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EIxx( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EIyy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EIyy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EIxy( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EIxy( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xleft( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xleft( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Xright( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Xright( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ytop( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ytop( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ybottom( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ybottom( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Origin( 
            /* [retval][out] */ IPoint2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Origin( 
            /* [in] */ IPoint2d *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Orientation( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CoordinateSystem( 
            /* [retval][out] */ CoordinateSystemType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_CoordinateSystem( 
            /* [in] */ CoordinateSystemType newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PrincipleDirection( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddProperties( 
            /* [in] */ IElasticProperties *props) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE TransformProperties( 
            /* [in] */ Float64 E,
            /* [retval][out] */ IShapeProperties **props) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IElasticPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IElasticProperties * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IElasticProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IElasticProperties * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EA )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EA )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Centroid )( 
            IElasticProperties * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Centroid )( 
            IElasticProperties * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EI11 )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EI22 )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EI12Max )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EI12Min )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EIxx )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EIxx )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EIyy )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EIyy )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EIxy )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EIxy )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xleft )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xleft )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Xright )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Xright )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ytop )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ytop )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ybottom )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ybottom )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Origin )( 
            IElasticProperties * This,
            /* [retval][out] */ IPoint2d **pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Origin )( 
            IElasticProperties * This,
            /* [in] */ IPoint2d *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Orientation )( 
            IElasticProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CoordinateSystem )( 
            IElasticProperties * This,
            /* [retval][out] */ CoordinateSystemType *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CoordinateSystem )( 
            IElasticProperties * This,
            /* [in] */ CoordinateSystemType newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PrincipleDirection )( 
            IElasticProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddProperties )( 
            IElasticProperties * This,
            /* [in] */ IElasticProperties *props);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *TransformProperties )( 
            IElasticProperties * This,
            /* [in] */ Float64 E,
            /* [retval][out] */ IShapeProperties **props);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IElasticProperties * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IElasticPropertiesVtbl;

    interface IElasticProperties
    {
        CONST_VTBL struct IElasticPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElasticProperties_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IElasticProperties_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IElasticProperties_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IElasticProperties_get_EA(This,pVal)	\
    ( (This)->lpVtbl -> get_EA(This,pVal) ) 

#define IElasticProperties_put_EA(This,newVal)	\
    ( (This)->lpVtbl -> put_EA(This,newVal) ) 

#define IElasticProperties_get_Centroid(This,pVal)	\
    ( (This)->lpVtbl -> get_Centroid(This,pVal) ) 

#define IElasticProperties_put_Centroid(This,newVal)	\
    ( (This)->lpVtbl -> put_Centroid(This,newVal) ) 

#define IElasticProperties_get_EI11(This,pVal)	\
    ( (This)->lpVtbl -> get_EI11(This,pVal) ) 

#define IElasticProperties_get_EI22(This,pVal)	\
    ( (This)->lpVtbl -> get_EI22(This,pVal) ) 

#define IElasticProperties_get_EI12Max(This,pVal)	\
    ( (This)->lpVtbl -> get_EI12Max(This,pVal) ) 

#define IElasticProperties_get_EI12Min(This,pVal)	\
    ( (This)->lpVtbl -> get_EI12Min(This,pVal) ) 

#define IElasticProperties_get_EIxx(This,pVal)	\
    ( (This)->lpVtbl -> get_EIxx(This,pVal) ) 

#define IElasticProperties_put_EIxx(This,newVal)	\
    ( (This)->lpVtbl -> put_EIxx(This,newVal) ) 

#define IElasticProperties_get_EIyy(This,pVal)	\
    ( (This)->lpVtbl -> get_EIyy(This,pVal) ) 

#define IElasticProperties_put_EIyy(This,newVal)	\
    ( (This)->lpVtbl -> put_EIyy(This,newVal) ) 

#define IElasticProperties_get_EIxy(This,pVal)	\
    ( (This)->lpVtbl -> get_EIxy(This,pVal) ) 

#define IElasticProperties_put_EIxy(This,newVal)	\
    ( (This)->lpVtbl -> put_EIxy(This,newVal) ) 

#define IElasticProperties_get_Xleft(This,pVal)	\
    ( (This)->lpVtbl -> get_Xleft(This,pVal) ) 

#define IElasticProperties_put_Xleft(This,newVal)	\
    ( (This)->lpVtbl -> put_Xleft(This,newVal) ) 

#define IElasticProperties_get_Xright(This,pVal)	\
    ( (This)->lpVtbl -> get_Xright(This,pVal) ) 

#define IElasticProperties_put_Xright(This,newVal)	\
    ( (This)->lpVtbl -> put_Xright(This,newVal) ) 

#define IElasticProperties_get_Ytop(This,pVal)	\
    ( (This)->lpVtbl -> get_Ytop(This,pVal) ) 

#define IElasticProperties_put_Ytop(This,newVal)	\
    ( (This)->lpVtbl -> put_Ytop(This,newVal) ) 

#define IElasticProperties_get_Ybottom(This,pVal)	\
    ( (This)->lpVtbl -> get_Ybottom(This,pVal) ) 

#define IElasticProperties_put_Ybottom(This,newVal)	\
    ( (This)->lpVtbl -> put_Ybottom(This,newVal) ) 

#define IElasticProperties_get_Origin(This,pVal)	\
    ( (This)->lpVtbl -> get_Origin(This,pVal) ) 

#define IElasticProperties_put_Origin(This,newVal)	\
    ( (This)->lpVtbl -> put_Origin(This,newVal) ) 

#define IElasticProperties_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IElasticProperties_put_Orientation(This,newVal)	\
    ( (This)->lpVtbl -> put_Orientation(This,newVal) ) 

#define IElasticProperties_get_CoordinateSystem(This,pVal)	\
    ( (This)->lpVtbl -> get_CoordinateSystem(This,pVal) ) 

#define IElasticProperties_put_CoordinateSystem(This,newVal)	\
    ( (This)->lpVtbl -> put_CoordinateSystem(This,newVal) ) 

#define IElasticProperties_get_PrincipleDirection(This,pVal)	\
    ( (This)->lpVtbl -> get_PrincipleDirection(This,pVal) ) 

#define IElasticProperties_AddProperties(This,props)	\
    ( (This)->lpVtbl -> AddProperties(This,props) ) 

#define IElasticProperties_TransformProperties(This,E,props)	\
    ( (This)->lpVtbl -> TransformProperties(This,E,props) ) 

#define IElasticProperties_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IElasticProperties_INTERFACE_DEFINED__ */


#ifndef __IMassProperties_INTERFACE_DEFINED__
#define __IMassProperties_INTERFACE_DEFINED__

/* interface IMassProperties */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IMassProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BA78A143-A0DA-4081-BAF5-C7BF7ACF9850")
    IMassProperties : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MassPerLength( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_MassPerLength( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddProperties( 
            /* [in] */ IMassProperties *props) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IMassPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMassProperties * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMassProperties * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMassProperties * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MassPerLength )( 
            IMassProperties * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_MassPerLength )( 
            IMassProperties * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddProperties )( 
            IMassProperties * This,
            /* [in] */ IMassProperties *props);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            IMassProperties * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } IMassPropertiesVtbl;

    interface IMassProperties
    {
        CONST_VTBL struct IMassPropertiesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMassProperties_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMassProperties_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMassProperties_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMassProperties_get_MassPerLength(This,pVal)	\
    ( (This)->lpVtbl -> get_MassPerLength(This,pVal) ) 

#define IMassProperties_put_MassPerLength(This,newVal)	\
    ( (This)->lpVtbl -> put_MassPerLength(This,newVal) ) 

#define IMassProperties_AddProperties(This,props)	\
    ( (This)->lpVtbl -> AddProperties(This,props) ) 

#define IMassProperties_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMassProperties_INTERFACE_DEFINED__ */


#ifndef __ISection_INTERFACE_DEFINED__
#define __ISection_INTERFACE_DEFINED__

/* interface ISection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6467790E-93DE-489b-9D3A-00F2A547A172")
    ISection : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BoundingBox( 
            /* [retval][out] */ IRect2d **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ElasticProperties( 
            /* [retval][out] */ IElasticProperties **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MassProperties( 
            /* [retval][out] */ IMassProperties **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ClipIn( 
            /* [in] */ IRect2d *rect,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ClipWithLine( 
            /* [in] */ ILine2d *line,
            /* [retval][out] */ ISection **section) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            ISection **clone) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISection * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BoundingBox )( 
            ISection * This,
            /* [retval][out] */ IRect2d **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ElasticProperties )( 
            ISection * This,
            /* [retval][out] */ IElasticProperties **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MassProperties )( 
            ISection * This,
            /* [retval][out] */ IMassProperties **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClipIn )( 
            ISection * This,
            /* [in] */ IRect2d *rect,
            /* [retval][out] */ ISection **section);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClipWithLine )( 
            ISection * This,
            /* [in] */ ILine2d *line,
            /* [retval][out] */ ISection **section);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            ISection * This,
            ISection **clone);
        
        END_INTERFACE
    } ISectionVtbl;

    interface ISection
    {
        CONST_VTBL struct ISectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISection_get_BoundingBox(This,pVal)	\
    ( (This)->lpVtbl -> get_BoundingBox(This,pVal) ) 

#define ISection_get_ElasticProperties(This,pVal)	\
    ( (This)->lpVtbl -> get_ElasticProperties(This,pVal) ) 

#define ISection_get_MassProperties(This,pVal)	\
    ( (This)->lpVtbl -> get_MassProperties(This,pVal) ) 

#define ISection_ClipIn(This,rect,section)	\
    ( (This)->lpVtbl -> ClipIn(This,rect,section) ) 

#define ISection_ClipWithLine(This,line,section)	\
    ( (This)->lpVtbl -> ClipWithLine(This,line,section) ) 

#define ISection_Clone(This,clone)	\
    ( (This)->lpVtbl -> Clone(This,clone) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISection_INTERFACE_DEFINED__ */


#ifndef __ICompositeSectionItem_INTERFACE_DEFINED__
#define __ICompositeSectionItem_INTERFACE_DEFINED__

/* interface ICompositeSectionItem */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeSectionItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ED88B503-F79D-4FAB-BE54-1DDCA670347B")
    ICompositeSectionItem : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Shape( 
            /* [in] */ IShape *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_E( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_E( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Density( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Density( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Void( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Void( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Structural( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Structural( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeSectionItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeSectionItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeSectionItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeSectionItem * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Shape )( 
            ICompositeSectionItem * This,
            /* [in] */ IShape *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_E )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_E )( 
            ICompositeSectionItem * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Density )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Density )( 
            ICompositeSectionItem * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Void )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Void )( 
            ICompositeSectionItem * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Structural )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Structural )( 
            ICompositeSectionItem * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeSectionItem * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeSectionItemVtbl;

    interface ICompositeSectionItem
    {
        CONST_VTBL struct ICompositeSectionItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeSectionItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeSectionItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeSectionItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeSectionItem_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICompositeSectionItem_putref_Shape(This,newVal)	\
    ( (This)->lpVtbl -> putref_Shape(This,newVal) ) 

#define ICompositeSectionItem_get_E(This,pVal)	\
    ( (This)->lpVtbl -> get_E(This,pVal) ) 

#define ICompositeSectionItem_put_E(This,newVal)	\
    ( (This)->lpVtbl -> put_E(This,newVal) ) 

#define ICompositeSectionItem_get_Density(This,pVal)	\
    ( (This)->lpVtbl -> get_Density(This,pVal) ) 

#define ICompositeSectionItem_put_Density(This,newVal)	\
    ( (This)->lpVtbl -> put_Density(This,newVal) ) 

#define ICompositeSectionItem_get_Void(This,pVal)	\
    ( (This)->lpVtbl -> get_Void(This,pVal) ) 

#define ICompositeSectionItem_put_Void(This,newVal)	\
    ( (This)->lpVtbl -> put_Void(This,newVal) ) 

#define ICompositeSectionItem_get_Structural(This,pVal)	\
    ( (This)->lpVtbl -> get_Structural(This,pVal) ) 

#define ICompositeSectionItem_put_Structural(This,newVal)	\
    ( (This)->lpVtbl -> put_Structural(This,newVal) ) 

#define ICompositeSectionItem_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeSectionItem_INTERFACE_DEFINED__ */


#ifndef __ICompositeSection_INTERFACE_DEFINED__
#define __ICompositeSection_INTERFACE_DEFINED__

/* interface ICompositeSection */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeSection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B65E675-01C8-11D5-8BAC-006097C68A9C")
    ICompositeSection : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeSectionItem **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSection( 
            /* [in] */ IShape *shape,
            /* [in] */ Float64 E,
            /* [in] */ Float64 density,
            /* [in] */ VARIANT_BOOL bVoid,
            /* [in] */ VARIANT_BOOL bStructural) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSectionEx( 
            /* [in] */ ICompositeSectionItem *sectionItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ ISection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeSectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeSection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeSection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeSection * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICompositeSection * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICompositeSection * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeSectionItem **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSection )( 
            ICompositeSection * This,
            /* [in] */ IShape *shape,
            /* [in] */ Float64 E,
            /* [in] */ Float64 density,
            /* [in] */ VARIANT_BOOL bVoid,
            /* [in] */ VARIANT_BOOL bStructural);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSectionEx )( 
            ICompositeSection * This,
            /* [in] */ ICompositeSectionItem *sectionItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICompositeSection * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICompositeSection * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ICompositeSection * This,
            /* [retval][out] */ ISection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ICompositeSection * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeSection * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeSectionVtbl;

    interface ICompositeSection
    {
        CONST_VTBL struct ICompositeSectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeSection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeSection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeSection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeSection_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ICompositeSection_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ICompositeSection_AddSection(This,shape,E,density,bVoid,bStructural)	\
    ( (This)->lpVtbl -> AddSection(This,shape,E,density,bVoid,bStructural) ) 

#define ICompositeSection_AddSectionEx(This,sectionItem)	\
    ( (This)->lpVtbl -> AddSectionEx(This,sectionItem) ) 

#define ICompositeSection_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ICompositeSection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ICompositeSection_get_Section(This,pVal)	\
    ( (This)->lpVtbl -> get_Section(This,pVal) ) 

#define ICompositeSection_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ICompositeSection_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeSection_INTERFACE_DEFINED__ */


#ifndef __ICompositeBeam_INTERFACE_DEFINED__
#define __ICompositeBeam_INTERFACE_DEFINED__

/* interface ICompositeBeam */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeBeam;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D7610038-0289-11D5-8BAE-006097C68A9C")
    ICompositeBeam : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Beam( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Beam( 
            /* [in] */ IShape *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EffectiveSlabWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EffectiveSlabWidth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TributarySlabWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TributarySlabWidth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GrossSlabDepth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_GrossSlabDepth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SacrificialDepth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SacrificialDepth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SlabE( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SlabE( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_SlabDensity( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_SlabDensity( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HaunchWidth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HaunchWidth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_HaunchDepth( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_HaunchDepth( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ ISection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeamE( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeamE( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_BeamDensity( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_BeamDensity( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_QSlab( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Q( 
            /* [in] */ Float64 location,
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeBeamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeBeam * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeBeam * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeBeam * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Beam )( 
            ICompositeBeam * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Beam )( 
            ICompositeBeam * This,
            /* [in] */ IShape *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EffectiveSlabWidth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EffectiveSlabWidth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TributarySlabWidth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TributarySlabWidth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_GrossSlabDepth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_GrossSlabDepth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SacrificialDepth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SacrificialDepth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlabE )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SlabE )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SlabDensity )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_SlabDensity )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HaunchWidth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HaunchWidth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HaunchDepth )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HaunchDepth )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ICompositeBeam * This,
            /* [retval][out] */ ISection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ICompositeBeam * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeamE )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeamE )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BeamDensity )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BeamDensity )( 
            ICompositeBeam * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QSlab )( 
            ICompositeBeam * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Q )( 
            ICompositeBeam * This,
            /* [in] */ Float64 location,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeBeam * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeBeamVtbl;

    interface ICompositeBeam
    {
        CONST_VTBL struct ICompositeBeamVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeBeam_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeBeam_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeBeam_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeBeam_get_Beam(This,pVal)	\
    ( (This)->lpVtbl -> get_Beam(This,pVal) ) 

#define ICompositeBeam_putref_Beam(This,newVal)	\
    ( (This)->lpVtbl -> putref_Beam(This,newVal) ) 

#define ICompositeBeam_get_EffectiveSlabWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_EffectiveSlabWidth(This,pVal) ) 

#define ICompositeBeam_put_EffectiveSlabWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_EffectiveSlabWidth(This,newVal) ) 

#define ICompositeBeam_get_TributarySlabWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_TributarySlabWidth(This,pVal) ) 

#define ICompositeBeam_put_TributarySlabWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_TributarySlabWidth(This,newVal) ) 

#define ICompositeBeam_get_GrossSlabDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_GrossSlabDepth(This,pVal) ) 

#define ICompositeBeam_put_GrossSlabDepth(This,newVal)	\
    ( (This)->lpVtbl -> put_GrossSlabDepth(This,newVal) ) 

#define ICompositeBeam_get_SacrificialDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_SacrificialDepth(This,pVal) ) 

#define ICompositeBeam_put_SacrificialDepth(This,newVal)	\
    ( (This)->lpVtbl -> put_SacrificialDepth(This,newVal) ) 

#define ICompositeBeam_get_SlabE(This,pVal)	\
    ( (This)->lpVtbl -> get_SlabE(This,pVal) ) 

#define ICompositeBeam_put_SlabE(This,newVal)	\
    ( (This)->lpVtbl -> put_SlabE(This,newVal) ) 

#define ICompositeBeam_get_SlabDensity(This,pVal)	\
    ( (This)->lpVtbl -> get_SlabDensity(This,pVal) ) 

#define ICompositeBeam_put_SlabDensity(This,newVal)	\
    ( (This)->lpVtbl -> put_SlabDensity(This,newVal) ) 

#define ICompositeBeam_get_HaunchWidth(This,pVal)	\
    ( (This)->lpVtbl -> get_HaunchWidth(This,pVal) ) 

#define ICompositeBeam_put_HaunchWidth(This,newVal)	\
    ( (This)->lpVtbl -> put_HaunchWidth(This,newVal) ) 

#define ICompositeBeam_get_HaunchDepth(This,pVal)	\
    ( (This)->lpVtbl -> get_HaunchDepth(This,pVal) ) 

#define ICompositeBeam_put_HaunchDepth(This,newVal)	\
    ( (This)->lpVtbl -> put_HaunchDepth(This,newVal) ) 

#define ICompositeBeam_get_Section(This,pVal)	\
    ( (This)->lpVtbl -> get_Section(This,pVal) ) 

#define ICompositeBeam_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ICompositeBeam_get_BeamE(This,pVal)	\
    ( (This)->lpVtbl -> get_BeamE(This,pVal) ) 

#define ICompositeBeam_put_BeamE(This,newVal)	\
    ( (This)->lpVtbl -> put_BeamE(This,newVal) ) 

#define ICompositeBeam_get_BeamDensity(This,pVal)	\
    ( (This)->lpVtbl -> get_BeamDensity(This,pVal) ) 

#define ICompositeBeam_put_BeamDensity(This,newVal)	\
    ( (This)->lpVtbl -> put_BeamDensity(This,newVal) ) 

#define ICompositeBeam_get_QSlab(This,pVal)	\
    ( (This)->lpVtbl -> get_QSlab(This,pVal) ) 

#define ICompositeBeam_get_Q(This,location,pVal)	\
    ( (This)->lpVtbl -> get_Q(This,location,pVal) ) 

#define ICompositeBeam_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeBeam_INTERFACE_DEFINED__ */


#ifndef __ICompositeSectionItemEx_INTERFACE_DEFINED__
#define __ICompositeSectionItemEx_INTERFACE_DEFINED__

/* interface ICompositeSectionItemEx */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeSectionItemEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6B42790-3DC8-487f-B33E-9B65167EFA3B")
    ICompositeSectionItemEx : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Shape( 
            /* [retval][out] */ IShape **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref] */ HRESULT STDMETHODCALLTYPE putref_Shape( 
            /* [in] */ IShape *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Efg( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Efg( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Ebg( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Ebg( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dfg( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dfg( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Dbg( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Dbg( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Structural( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Structural( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeSectionItemExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeSectionItemEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeSectionItemEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeSectionItemEx * This);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Shape )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ IShape **pVal);
        
        /* [helpcontext][helpstring][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Shape )( 
            ICompositeSectionItemEx * This,
            /* [in] */ IShape *newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Efg )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Efg )( 
            ICompositeSectionItemEx * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Ebg )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Ebg )( 
            ICompositeSectionItemEx * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dfg )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dfg )( 
            ICompositeSectionItemEx * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dbg )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Dbg )( 
            ICompositeSectionItemEx * This,
            /* [in] */ Float64 newVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Structural )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Structural )( 
            ICompositeSectionItemEx * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeSectionItemEx * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeSectionItemExVtbl;

    interface ICompositeSectionItemEx
    {
        CONST_VTBL struct ICompositeSectionItemExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeSectionItemEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeSectionItemEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeSectionItemEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeSectionItemEx_get_Shape(This,pVal)	\
    ( (This)->lpVtbl -> get_Shape(This,pVal) ) 

#define ICompositeSectionItemEx_putref_Shape(This,newVal)	\
    ( (This)->lpVtbl -> putref_Shape(This,newVal) ) 

#define ICompositeSectionItemEx_get_Efg(This,pVal)	\
    ( (This)->lpVtbl -> get_Efg(This,pVal) ) 

#define ICompositeSectionItemEx_put_Efg(This,newVal)	\
    ( (This)->lpVtbl -> put_Efg(This,newVal) ) 

#define ICompositeSectionItemEx_get_Ebg(This,pVal)	\
    ( (This)->lpVtbl -> get_Ebg(This,pVal) ) 

#define ICompositeSectionItemEx_put_Ebg(This,newVal)	\
    ( (This)->lpVtbl -> put_Ebg(This,newVal) ) 

#define ICompositeSectionItemEx_get_Dfg(This,pVal)	\
    ( (This)->lpVtbl -> get_Dfg(This,pVal) ) 

#define ICompositeSectionItemEx_put_Dfg(This,newVal)	\
    ( (This)->lpVtbl -> put_Dfg(This,newVal) ) 

#define ICompositeSectionItemEx_get_Dbg(This,pVal)	\
    ( (This)->lpVtbl -> get_Dbg(This,pVal) ) 

#define ICompositeSectionItemEx_put_Dbg(This,newVal)	\
    ( (This)->lpVtbl -> put_Dbg(This,newVal) ) 

#define ICompositeSectionItemEx_get_Structural(This,pVal)	\
    ( (This)->lpVtbl -> get_Structural(This,pVal) ) 

#define ICompositeSectionItemEx_put_Structural(This,newVal)	\
    ( (This)->lpVtbl -> put_Structural(This,newVal) ) 

#define ICompositeSectionItemEx_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeSectionItemEx_INTERFACE_DEFINED__ */


#ifndef __ICompositeSectionEx_INTERFACE_DEFINED__
#define __ICompositeSectionEx_INTERFACE_DEFINED__

/* interface ICompositeSectionEx */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICompositeSectionEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDEA2BF6-8E57-4bfa-8CD6-A007C6E1E032")
    ICompositeSectionEx : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeSectionItemEx **pVal) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSection( 
            /* [in] */ IShape *shape,
            /* [in] */ Float64 Efg,
            /* [in] */ Float64 Ebg,
            /* [in] */ Float64 Dfg,
            /* [in] */ Float64 Dbg,
            /* [in] */ VARIANT_BOOL bStructural) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE AddSectionEx( 
            /* [in] */ ICompositeSectionItemEx *sectionItem) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ CollectionIndexType idx) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Section( 
            /* [retval][out] */ ISection **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_XYPosition( 
            /* [retval][out] */ IXYPosition **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_StructuredStorage( 
            /* [retval][out] */ IStructuredStorage2 **pStrStg) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICompositeSectionExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICompositeSectionEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICompositeSectionEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICompositeSectionEx * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            ICompositeSectionEx * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            ICompositeSectionEx * This,
            /* [in] */ CollectionIndexType idx,
            /* [retval][out] */ ICompositeSectionItemEx **pVal);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSection )( 
            ICompositeSectionEx * This,
            /* [in] */ IShape *shape,
            /* [in] */ Float64 Efg,
            /* [in] */ Float64 Ebg,
            /* [in] */ Float64 Dfg,
            /* [in] */ Float64 Dbg,
            /* [in] */ VARIANT_BOOL bStructural);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSectionEx )( 
            ICompositeSectionEx * This,
            /* [in] */ ICompositeSectionItemEx *sectionItem);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            ICompositeSectionEx * This,
            /* [in] */ CollectionIndexType idx);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            ICompositeSectionEx * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Section )( 
            ICompositeSectionEx * This,
            /* [retval][out] */ ISection **pVal);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_XYPosition )( 
            ICompositeSectionEx * This,
            /* [retval][out] */ IXYPosition **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StructuredStorage )( 
            ICompositeSectionEx * This,
            /* [retval][out] */ IStructuredStorage2 **pStrStg);
        
        END_INTERFACE
    } ICompositeSectionExVtbl;

    interface ICompositeSectionEx
    {
        CONST_VTBL struct ICompositeSectionExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompositeSectionEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICompositeSectionEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICompositeSectionEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICompositeSectionEx_get__NewEnum(This,pVal)	\
    ( (This)->lpVtbl -> get__NewEnum(This,pVal) ) 

#define ICompositeSectionEx_get_Item(This,idx,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,idx,pVal) ) 

#define ICompositeSectionEx_AddSection(This,shape,Efg,Ebg,Dfg,Dbg,bStructural)	\
    ( (This)->lpVtbl -> AddSection(This,shape,Efg,Ebg,Dfg,Dbg,bStructural) ) 

#define ICompositeSectionEx_AddSectionEx(This,sectionItem)	\
    ( (This)->lpVtbl -> AddSectionEx(This,sectionItem) ) 

#define ICompositeSectionEx_Remove(This,idx)	\
    ( (This)->lpVtbl -> Remove(This,idx) ) 

#define ICompositeSectionEx_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define ICompositeSectionEx_get_Section(This,pVal)	\
    ( (This)->lpVtbl -> get_Section(This,pVal) ) 

#define ICompositeSectionEx_get_XYPosition(This,pVal)	\
    ( (This)->lpVtbl -> get_XYPosition(This,pVal) ) 

#define ICompositeSectionEx_get_StructuredStorage(This,pStrStg)	\
    ( (This)->lpVtbl -> get_StructuredStorage(This,pStrStg) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICompositeSectionEx_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ElasticProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("FD7B2E32-6DB3-4BF2-8A0A-484B19FD1CE6")
ElasticProperties;
#endif

EXTERN_C const CLSID CLSID_MassProperties;

#ifdef __cplusplus

class DECLSPEC_UUID("3925A3FA-34CD-4E06-AEDF-BCD1773E0810")
MassProperties;
#endif

EXTERN_C const CLSID CLSID_CompositeSectionItem;

#ifdef __cplusplus

class DECLSPEC_UUID("9A0C379F-0945-41E5-8053-FD77B4FDBF59")
CompositeSectionItem;
#endif

EXTERN_C const CLSID CLSID_CompositeSection;

#ifdef __cplusplus

class DECLSPEC_UUID("9B65E676-01C8-11D5-8BAC-006097C68A9C")
CompositeSection;
#endif

EXTERN_C const CLSID CLSID_CompositeBeam;

#ifdef __cplusplus

class DECLSPEC_UUID("D7610039-0289-11D5-8BAE-006097C68A9C")
CompositeBeam;
#endif

EXTERN_C const CLSID CLSID_CompositeSectionItemEx;

#ifdef __cplusplus

class DECLSPEC_UUID("94267249-3C7D-40a3-BB21-DD8916BA4DE0")
CompositeSectionItemEx;
#endif

EXTERN_C const CLSID CLSID_CompositeSectionEx;

#ifdef __cplusplus

class DECLSPEC_UUID("85AB469B-A6A3-4057-848A-1572DAD74DE0")
CompositeSectionEx;
#endif
#endif /* __WBFLSections_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


