

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jun 29 14:41:31 2017
 */
/* Compiler settings for ..\..\Include\WBFLLBAMAnalysisUtility.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_WBFLLBAMAnalysisUtility,0x8B25EF41,0x3951,0x4A46,0x9D,0x1E,0xDF,0xA4,0x28,0x0C,0xC8,0x74);


MIDL_DEFINE_GUID(IID, IID_ILBAMAnalysisEngine,0xA191EA1A,0x4FCA,0x470D,0xAF,0x9A,0x24,0x29,0x69,0xF7,0xF8,0x6F);


MIDL_DEFINE_GUID(IID, IID_ISupportProgressMonitorForEngine,0x6857CDD0,0x169F,0x4ba3,0xA7,0x3C,0x51,0xB4,0x91,0xEB,0x72,0x73);


MIDL_DEFINE_GUID(IID, IID_ILBAMModelEnveloper,0xE04FBF3C,0xC12C,0x43CE,0x9D,0xFF,0xC5,0x92,0xF1,0x32,0x8A,0xEA);


MIDL_DEFINE_GUID(CLSID, CLSID_LBAMAnalysisEngine,0x3D1EF310,0xE132,0x4DF4,0x85,0xCC,0x3A,0x74,0x67,0xF9,0x48,0xE6);


MIDL_DEFINE_GUID(CLSID, CLSID_LBAMModelEnveloper,0x48715D04,0x3187,0x4ECD,0xA7,0xB4,0x3A,0xC4,0xF3,0xF5,0x8C,0xA7);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



