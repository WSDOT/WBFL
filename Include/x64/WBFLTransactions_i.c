

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:23:24 2017
 */
/* Compiler settings for ..\Include\WBFLTransactions.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_WBFLTransactions,0x081C49DE,0xFBE8,0x4C8D,0xBE,0xEC,0xF1,0x3E,0xCF,0xF2,0xB5,0x6C);


MIDL_DEFINE_GUID(IID, IID_IWBFLTransaction,0xDBB7742C,0xCD24,0x45d6,0x89,0x7B,0x58,0xA9,0x1D,0xD2,0x05,0xF7);


MIDL_DEFINE_GUID(IID, IID_IWBFLMacroTransaction,0x1B39F34E,0x247E,0x47EF,0xB7,0x50,0x50,0x85,0x47,0x84,0xD0,0xC4);


MIDL_DEFINE_GUID(IID, IID_IWBFLMacroAdapter,0x2F8F8D41,0x5D23,0x45DC,0x9C,0x94,0xEC,0x70,0xCF,0xE5,0x3F,0x07);


MIDL_DEFINE_GUID(IID, IID_IWBFLTransactionMgr,0xAF78349C,0xCBC3,0x46AE,0xAC,0xD8,0x08,0x40,0x8F,0x0A,0x62,0x31);


MIDL_DEFINE_GUID(IID, IID_IWBFLSupportTransactions,0x01D989A2,0x2D02,0x462f,0xBD,0x20,0xDB,0x2B,0xAA,0x42,0x60,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_WBFLTransactionMgr,0x05773828,0x07E0,0x4BE1,0xB9,0x9C,0xEF,0x6D,0x8E,0x03,0x26,0xAE);


MIDL_DEFINE_GUID(CLSID, CLSID_WBFLMacroTransaction,0x8CF1CDEA,0xD489,0x41C3,0x8A,0x90,0x01,0x0D,0x89,0x47,0x42,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID_WBFLMacroAdapter,0x125EC02E,0xC6FD,0x4385,0x93,0x1D,0xE9,0xC4,0x4B,0xEF,0xB9,0x56);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



