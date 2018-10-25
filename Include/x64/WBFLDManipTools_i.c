

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, LIBID_WBFLDManipTools,0xB7B9C36E,0xFEAF,0x43BB,0x89,0x07,0xC9,0x8A,0x0E,0xF3,0x22,0x4E);


MIDL_DEFINE_GUID(CLSID, CLSID_PolyLineDisplayObject,0x341A682F,0x5B58,0x4f63,0x81,0x90,0x88,0xBF,0x39,0x70,0xFB,0x45);


MIDL_DEFINE_GUID(CLSID, CLSID_HorzCurveDisplayObject,0x7DBA44AA,0x1542,0x4470,0x87,0x19,0x21,0x58,0x0A,0x68,0x22,0xB5);


MIDL_DEFINE_GUID(CLSID, CLSID_GraphXyDisplayObject,0x06C90828,0x5269,0x4b98,0x97,0xE6,0xAE,0xCD,0xDF,0x4B,0x07,0x64);


MIDL_DEFINE_GUID(CLSID, CLSID_DataSet2d,0x4792CF33,0xB6FD,0x423F,0x90,0xDE,0x31,0x43,0x56,0xA2,0x28,0x48);


MIDL_DEFINE_GUID(CLSID, CLSID_LegendDisplayObject,0xC2EC59B5,0xBAA1,0x437d,0x89,0xCB,0x19,0xAD,0x85,0xED,0x9F,0x04);


MIDL_DEFINE_GUID(CLSID, CLSID_LegendEntry,0x951403BB,0x85F3,0x4443,0x8E,0xE9,0x4F,0xFD,0xB3,0x38,0xF3,0xF5);


MIDL_DEFINE_GUID(CLSID, CLSID_DManipToolsDisplayObjectFactory,0xD7C33DA2,0xEE8F,0x49a1,0x9A,0x13,0x86,0x53,0x80,0x92,0x62,0xE9);


MIDL_DEFINE_GUID(CLSID, CLSID_GraphXyDataProvider,0x0462D6DF,0x25DB,0x4fa0,0xB8,0xB2,0x7B,0x85,0x5A,0x70,0x2A,0x99);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



