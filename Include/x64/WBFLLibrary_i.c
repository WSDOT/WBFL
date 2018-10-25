

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:42:37 2017
 */
/* Compiler settings for ..\Include\WBFLLibrary.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_WBFLLibrary,0x627C17C7,0x86D8,0x4966,0x8C,0x1B,0x61,0xF7,0x84,0x03,0xDD,0x09);


MIDL_DEFINE_GUID(IID, IID_ILibraryEntry,0xCD76D614,0x68E6,0x4b49,0xB8,0xD4,0x41,0x60,0xB0,0xFB,0x7F,0x33);


MIDL_DEFINE_GUID(IID, IID_ILibraryEntryEvents,0x344D345E,0x987D,0x4f0c,0x9D,0x41,0x9D,0x40,0x81,0x18,0xC3,0xB5);


MIDL_DEFINE_GUID(IID, IID_IEnumLibraryEntry,0x82556E2C,0x659C,0x481a,0x8B,0x92,0x39,0xEE,0x77,0xC4,0x6A,0xFE);


MIDL_DEFINE_GUID(IID, IID_ILibrary,0xE15347B8,0xCB99,0x4D3D,0x98,0x61,0x6B,0x49,0x54,0x17,0x3A,0xD6);


MIDL_DEFINE_GUID(IID, IID_IEnumLibrary,0x18B051F5,0xD3B5,0x4228,0xBD,0x8D,0x88,0x53,0x38,0x56,0x90,0x5F);


MIDL_DEFINE_GUID(IID, IID_ILibraryMgr,0x63BC88AF,0x2C7D,0x4224,0x90,0xB7,0x5C,0x07,0x8C,0x09,0x83,0xCE);


MIDL_DEFINE_GUID(IID, IID_ILibraryMgrEvents,0x47D4D00D,0x1EFF,0x4a34,0x9F,0x92,0xDD,0x67,0x77,0xF1,0x9A,0xF3);


MIDL_DEFINE_GUID(IID, IID_ILibraryEvents,0x623332B2,0xB575,0x4b2e,0x88,0xF3,0x82,0x99,0x65,0x08,0x91,0xDE);


MIDL_DEFINE_GUID(IID, IID_ILibraryViewer,0xA6A3E5A8,0xC81D,0x46F1,0x8C,0x58,0x84,0x8C,0xB3,0x8B,0x6D,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_LibraryMgr,0x0795E1D7,0x3F1B,0x4E6A,0xB0,0x10,0x7A,0xE0,0x7A,0x5E,0xB7,0x0C);


MIDL_DEFINE_GUID(CLSID, CLSID_Library,0x21270B15,0x4445,0x4D09,0xAB,0xF2,0xF3,0x8D,0x71,0x24,0x72,0xEF);


MIDL_DEFINE_GUID(IID, IID_ILibraryViewerEvents,0x74C5DA97,0x57F1,0x4FE2,0xB6,0xC0,0x92,0x9C,0x48,0xB5,0xA8,0xF2);


MIDL_DEFINE_GUID(CLSID, CLSID_LibraryViewer,0x14361D58,0xAF5B,0x11D4,0x8B,0x4D,0x00,0x60,0x97,0xC6,0x8A,0x9C);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



