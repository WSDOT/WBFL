

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:40:02 2017
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_STORAGETESTLib,0x71A9DDC8,0x55D1,0x11D5,0xB0,0x05,0x00,0x10,0x5A,0x9A,0xF9,0x85);


MIDL_DEFINE_GUID(IID, IID_IPShape,0x2930A1A6,0x55D2,0x11d5,0xB0,0x05,0x00,0x10,0x5A,0x9A,0xF9,0x85);


MIDL_DEFINE_GUID(IID, IID_IPRectangle,0x3369971F,0xBA89,0x41c2,0x90,0x47,0x84,0xC1,0x69,0x8A,0xD9,0x5C);


MIDL_DEFINE_GUID(IID, IID_IPCircle,0x29F6E6BF,0x0FE1,0x461e,0x87,0x26,0xFB,0x15,0xAB,0xF9,0xC8,0x12);


MIDL_DEFINE_GUID(IID, IID_IPCompositeShape,0x15FFC95E,0x8857,0x4e41,0xAE,0xDE,0x82,0x43,0x4A,0xAF,0x1F,0x5F);


MIDL_DEFINE_GUID(CLSID, CLSID_PRectangle,0xA7DDF82E,0x7884,0x4f59,0xAB,0x4D,0xF0,0x98,0xEE,0x45,0x10,0xA0);


MIDL_DEFINE_GUID(CLSID, CLSID_PCircle,0xFEA8093A,0x88CA,0x44ff,0xB3,0xF7,0xF1,0x7A,0x3D,0x69,0xF0,0xA2);


MIDL_DEFINE_GUID(CLSID, CLSID_PCompositeShape,0xEDC65DDC,0xED4C,0x41d3,0xBC,0x4B,0x5C,0x65,0x15,0xEF,0xB7,0x95);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



