

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:40:10 2017
 */
/* Compiler settings for StorageTest.idl:
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


#ifndef __StorageTest_h__
#define __StorageTest_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPShape_FWD_DEFINED__
#define __IPShape_FWD_DEFINED__
typedef interface IPShape IPShape;

#endif 	/* __IPShape_FWD_DEFINED__ */


#ifndef __IPRectangle_FWD_DEFINED__
#define __IPRectangle_FWD_DEFINED__
typedef interface IPRectangle IPRectangle;

#endif 	/* __IPRectangle_FWD_DEFINED__ */


#ifndef __IPCircle_FWD_DEFINED__
#define __IPCircle_FWD_DEFINED__
typedef interface IPCircle IPCircle;

#endif 	/* __IPCircle_FWD_DEFINED__ */


#ifndef __IPCompositeShape_FWD_DEFINED__
#define __IPCompositeShape_FWD_DEFINED__
typedef interface IPCompositeShape IPCompositeShape;

#endif 	/* __IPCompositeShape_FWD_DEFINED__ */


#ifndef __PRectangle_FWD_DEFINED__
#define __PRectangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class PRectangle PRectangle;
#else
typedef struct PRectangle PRectangle;
#endif /* __cplusplus */

#endif 	/* __PRectangle_FWD_DEFINED__ */


#ifndef __PCircle_FWD_DEFINED__
#define __PCircle_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCircle PCircle;
#else
typedef struct PCircle PCircle;
#endif /* __cplusplus */

#endif 	/* __PCircle_FWD_DEFINED__ */


#ifndef __PCompositeShape_FWD_DEFINED__
#define __PCompositeShape_FWD_DEFINED__

#ifdef __cplusplus
typedef class PCompositeShape PCompositeShape;
#else
typedef struct PCompositeShape PCompositeShape;
#endif /* __cplusplus */

#endif 	/* __PCompositeShape_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "WBFLTypes.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __STORAGETESTLib_LIBRARY_DEFINED__
#define __STORAGETESTLib_LIBRARY_DEFINED__

/* library STORAGETESTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_STORAGETESTLib;

#ifndef __IPShape_INTERFACE_DEFINED__
#define __IPShape_INTERFACE_DEFINED__

/* interface IPShape */
/* [unique][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2930A1A6-55D2-11d5-B005-00105A9AF985")
    IPShape : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_X( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_X( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Y( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Y( 
            /* [in] */ Float64 newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsComposite( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ CollectionIndexType *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPShape **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            IPShape *__MIDL__IPShape0000) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPShape * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsComposite )( 
            IPShape * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPShape * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPShape * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPShape **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPShape * This,
            IPShape *__MIDL__IPShape0000);
        
        END_INTERFACE
    } IPShapeVtbl;

    interface IPShape
    {
        CONST_VTBL struct IPShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPShape_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IPShape_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IPShape_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IPShape_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IPShape_get_IsComposite(This,pVal)	\
    ( (This)->lpVtbl -> get_IsComposite(This,pVal) ) 

#define IPShape_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPShape_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPShape_Add(This,__MIDL__IPShape0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IPShape0000) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPShape_INTERFACE_DEFINED__ */


#ifndef __IPRectangle_INTERFACE_DEFINED__
#define __IPRectangle_INTERFACE_DEFINED__

/* interface IPRectangle */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3369971F-BA89-41c2-9047-84C1698AD95C")
    IPRectangle : public IPShape
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPRectangle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPRectangle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPRectangle * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPRectangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPRectangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPRectangle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPRectangle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsComposite )( 
            IPRectangle * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPRectangle * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPRectangle * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPShape **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPRectangle * This,
            IPShape *__MIDL__IPShape0000);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IPRectangle * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Name )( 
            IPRectangle * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IPRectangleVtbl;

    interface IPRectangle
    {
        CONST_VTBL struct IPRectangleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPRectangle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPRectangle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPRectangle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPRectangle_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IPRectangle_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IPRectangle_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IPRectangle_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IPRectangle_get_IsComposite(This,pVal)	\
    ( (This)->lpVtbl -> get_IsComposite(This,pVal) ) 

#define IPRectangle_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPRectangle_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPRectangle_Add(This,__MIDL__IPShape0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IPShape0000) ) 


#define IPRectangle_get_Name(This,pVal)	\
    ( (This)->lpVtbl -> get_Name(This,pVal) ) 

#define IPRectangle_put_Name(This,newVal)	\
    ( (This)->lpVtbl -> put_Name(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPRectangle_INTERFACE_DEFINED__ */


#ifndef __IPCircle_INTERFACE_DEFINED__
#define __IPCircle_INTERFACE_DEFINED__

/* interface IPCircle */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPCircle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29F6E6BF-0FE1-461e-8726-FB15ABF9C812")
    IPCircle : public IPShape
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Diameter( 
            /* [retval][out] */ Float64 *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Diameter( 
            /* [in] */ Float64 newVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPCircleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCircle * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCircle * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCircle * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPCircle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPCircle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPCircle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPCircle * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsComposite )( 
            IPCircle * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPCircle * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPCircle * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPShape **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPCircle * This,
            IPShape *__MIDL__IPShape0000);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Diameter )( 
            IPCircle * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Diameter )( 
            IPCircle * This,
            /* [in] */ Float64 newVal);
        
        END_INTERFACE
    } IPCircleVtbl;

    interface IPCircle
    {
        CONST_VTBL struct IPCircleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCircle_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPCircle_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPCircle_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPCircle_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IPCircle_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IPCircle_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IPCircle_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IPCircle_get_IsComposite(This,pVal)	\
    ( (This)->lpVtbl -> get_IsComposite(This,pVal) ) 

#define IPCircle_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPCircle_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPCircle_Add(This,__MIDL__IPShape0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IPShape0000) ) 


#define IPCircle_get_Diameter(This,pVal)	\
    ( (This)->lpVtbl -> get_Diameter(This,pVal) ) 

#define IPCircle_put_Diameter(This,newVal)	\
    ( (This)->lpVtbl -> put_Diameter(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPCircle_INTERFACE_DEFINED__ */


#ifndef __IPCompositeShape_INTERFACE_DEFINED__
#define __IPCompositeShape_INTERFACE_DEFINED__

/* interface IPCompositeShape */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IPCompositeShape;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("15FFC95E-8857-4e41-AEDE-82434AAF1F5F")
    IPCompositeShape : public IPShape
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IPCompositeShapeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPCompositeShape * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPCompositeShape * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPCompositeShape * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_X )( 
            IPCompositeShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_X )( 
            IPCompositeShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Y )( 
            IPCompositeShape * This,
            /* [retval][out] */ Float64 *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Y )( 
            IPCompositeShape * This,
            /* [in] */ Float64 newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsComposite )( 
            IPCompositeShape * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IPCompositeShape * This,
            /* [retval][out] */ CollectionIndexType *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IPCompositeShape * This,
            /* [in] */ CollectionIndexType index,
            /* [retval][out] */ IPShape **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IPCompositeShape * This,
            IPShape *__MIDL__IPShape0000);
        
        END_INTERFACE
    } IPCompositeShapeVtbl;

    interface IPCompositeShape
    {
        CONST_VTBL struct IPCompositeShapeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPCompositeShape_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPCompositeShape_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPCompositeShape_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPCompositeShape_get_X(This,pVal)	\
    ( (This)->lpVtbl -> get_X(This,pVal) ) 

#define IPCompositeShape_put_X(This,newVal)	\
    ( (This)->lpVtbl -> put_X(This,newVal) ) 

#define IPCompositeShape_get_Y(This,pVal)	\
    ( (This)->lpVtbl -> get_Y(This,pVal) ) 

#define IPCompositeShape_put_Y(This,newVal)	\
    ( (This)->lpVtbl -> put_Y(This,newVal) ) 

#define IPCompositeShape_get_IsComposite(This,pVal)	\
    ( (This)->lpVtbl -> get_IsComposite(This,pVal) ) 

#define IPCompositeShape_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IPCompositeShape_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IPCompositeShape_Add(This,__MIDL__IPShape0000)	\
    ( (This)->lpVtbl -> Add(This,__MIDL__IPShape0000) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPCompositeShape_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PRectangle;

#ifdef __cplusplus

class DECLSPEC_UUID("A7DDF82E-7884-4f59-AB4D-F098EE4510A0")
PRectangle;
#endif

EXTERN_C const CLSID CLSID_PCircle;

#ifdef __cplusplus

class DECLSPEC_UUID("FEA8093A-88CA-44ff-B3F7-F17A3D69F0A2")
PCircle;
#endif

EXTERN_C const CLSID CLSID_PCompositeShape;

#ifdef __cplusplus

class DECLSPEC_UUID("EDC65DDC-ED4C-41d3-BC4B-5C6515EFB795")
PCompositeShape;
#endif
#endif /* __STORAGETESTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


