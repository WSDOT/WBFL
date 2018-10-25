

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:28:07 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMUtility.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
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

MIDL_DEFINE_GUID(IID, LIBID_WBFLLBAMUtility,0x12D5CC49,0xBF21,0x11D5,0xB0,0x75,0x00,0x10,0x5A,0x9A,0xF9,0x85);


MIDL_DEFINE_GUID(IID, IID_ILBAMFactory,0x12D5CC56,0xBF21,0x11D5,0xB0,0x75,0x00,0x10,0x5A,0x9A,0xF9,0x85);


MIDL_DEFINE_GUID(IID, IID_ILBAMLRFDFactory,0x1ACF6808,0x3391,0x4902,0x80,0x32,0x93,0x69,0x58,0x68,0x21,0x74);


MIDL_DEFINE_GUID(IID, IID_ILBAMLRFDFactory2,0xB62C903B,0xBDE8,0x4317,0x99,0x45,0x26,0x7E,0xD0,0x15,0xEB,0x69);


MIDL_DEFINE_GUID(IID, IID_ILBAMLRFDFactory3,0xFEF8CA66,0x2A31,0x4663,0xA0,0x01,0x9D,0xC1,0x70,0x0E,0xCB,0xDD);


MIDL_DEFINE_GUID(CLSID, CLSID_LRFDFactory,0x12D5CC57,0xBF21,0x11D5,0xB0,0x75,0x00,0x10,0x5A,0x9A,0xF9,0x85);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



