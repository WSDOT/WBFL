

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jun 23 11:25:39 2017
 */
/* Compiler settings for ..\Include\WBFLBridgeGeometry.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "WBFLBridgeGeometry.h"

#define TYPE_FORMAT_STRING_SIZE   1731                              
#define PROC_FORMAT_STRING_SIZE   6819                              
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _WBFLBridgeGeometry_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } WBFLBridgeGeometry_MIDL_TYPE_FORMAT_STRING;

typedef struct _WBFLBridgeGeometry_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } WBFLBridgeGeometry_MIDL_PROC_FORMAT_STRING;

typedef struct _WBFLBridgeGeometry_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } WBFLBridgeGeometry_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const WBFLBridgeGeometry_MIDL_TYPE_FORMAT_STRING WBFLBridgeGeometry__MIDL_TypeFormatString;
extern const WBFLBridgeGeometry_MIDL_PROC_FORMAT_STRING WBFLBridgeGeometry__MIDL_ProcFormatString;
extern const WBFLBridgeGeometry_MIDL_EXPR_FORMAT_STRING WBFLBridgeGeometry__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPierLine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPierLine_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEnumPierLines_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEnumPierLines_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPierLineCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPierLineCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILayoutLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ILayoutLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAlignmentOffsetLayoutLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAlignmentOffsetLayoutLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISimpleLayoutLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISimpleLayoutLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IUniformSpacingLayoutLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IUniformSpacingLayoutLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGirderLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGirderLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISingleGirderLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISingleGirderLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISimpleGirderLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISimpleGirderLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IGirderLine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IGirderLine_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDiaphragmLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDiaphragmLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISingleDiaphragmLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISingleDiaphragmLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IThroughPointDiaphragmLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IThroughPointDiaphragmLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IEqualSpaceDiaphragmLineFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IEqualSpaceDiaphragmLineFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDiaphragmLine_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDiaphragmLine_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDeckBoundary_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDeckBoundary_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IDeckBoundaryFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IDeckBoundaryFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ISimpleDeckBoundaryFactory_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ISimpleDeckBoundaryFactory_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IBridgeGeometry_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IBridgeGeometry_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const WBFLBridgeGeometry_MIDL_PROC_FORMAT_STRING WBFLBridgeGeometry__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_ID */


	/* Procedure get_ID */


	/* Procedure get_AlignmentID */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x2c ),	/* 44 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 16 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter ID */

/* 26 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 32 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Station */

/* 38 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 40 */	NdrFcLong( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x4 ),	/* 4 */
/* 46 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 64 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 66 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 68 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Direction */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x5 ),	/* 5 */
/* 84 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 102 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Normal */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x6 ),	/* 6 */
/* 122 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 130 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 140 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 142 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 144 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 148 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Skew */

/* 152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x7 ),	/* 7 */
/* 160 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 166 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 168 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 178 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 180 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 182 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */

	/* Return value */

/* 184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 186 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BridgeAlignmentID */


	/* Procedure get_LayoutLineIDInc */


	/* Procedure get_Index */

/* 190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 198 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x2c ),	/* 44 */
/* 204 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 206 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter inc */


	/* Parameter pVal */

/* 216 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 218 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 220 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DiaphragmLineID */


	/* Procedure get_LeftLayoutLineID */


	/* Procedure get_EndPierID */


	/* Procedure get_ID */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x9 ),	/* 9 */
/* 236 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 240 */	NdrFcShort( 0x2c ),	/* 44 */
/* 242 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 244 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 254 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 256 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 258 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 260 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 262 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 264 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NextPierLine */

/* 266 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 268 */	NdrFcLong( 0x0 ),	/* 0 */
/* 272 */	NdrFcShort( 0xa ),	/* 10 */
/* 274 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 280 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 282 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 292 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 294 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 296 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 298 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 300 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 302 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PrevPierLine */

/* 304 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 306 */	NdrFcLong( 0x0 ),	/* 0 */
/* 310 */	NdrFcShort( 0xb ),	/* 11 */
/* 312 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 318 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 320 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 330 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 332 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 334 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BearingOffset */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xc ),	/* 12 */
/* 350 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 352 */	NdrFcShort( 0x6 ),	/* 6 */
/* 354 */	NdrFcShort( 0x2c ),	/* 44 */
/* 356 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 358 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 368 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 370 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 372 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter brgOffset */

/* 374 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 376 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 378 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 382 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BearingOffset */

/* 386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0xd ),	/* 13 */
/* 394 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 396 */	NdrFcShort( 0x16 ),	/* 22 */
/* 398 */	NdrFcShort( 0x8 ),	/* 8 */
/* 400 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 402 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x20 ),	/* 32 */

	/* Parameter pierFace */

/* 412 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 414 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 416 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter brgOffset */

/* 418 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 420 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 422 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 426 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BearingOffsetMeasurementType */

/* 430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0xe ),	/* 14 */
/* 438 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 440 */	NdrFcShort( 0x6 ),	/* 6 */
/* 442 */	NdrFcShort( 0x22 ),	/* 34 */
/* 444 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 446 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 456 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 458 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 460 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 462 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 464 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 466 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 468 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 470 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BearingOffsetMeasurementType */

/* 474 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 476 */	NdrFcLong( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0xf ),	/* 15 */
/* 482 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 484 */	NdrFcShort( 0xc ),	/* 12 */
/* 486 */	NdrFcShort( 0x8 ),	/* 8 */
/* 488 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 490 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 500 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 502 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 504 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 506 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 508 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 510 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 512 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 514 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndDistance */


	/* Procedure get_EndDistance */

/* 518 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 520 */	NdrFcLong( 0x0 ),	/* 0 */
/* 524 */	NdrFcShort( 0x10 ),	/* 16 */
/* 526 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 528 */	NdrFcShort( 0x6 ),	/* 6 */
/* 530 */	NdrFcShort( 0x2c ),	/* 44 */
/* 532 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 534 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */


	/* Parameter pierFace */

/* 544 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 546 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 548 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pEndDist */


	/* Parameter endDist */

/* 550 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 552 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 554 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 556 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 558 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 560 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndDistance */

/* 562 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 564 */	NdrFcLong( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x11 ),	/* 17 */
/* 570 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 572 */	NdrFcShort( 0x16 ),	/* 22 */
/* 574 */	NdrFcShort( 0x8 ),	/* 8 */
/* 576 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 578 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0x20 ),	/* 32 */

	/* Parameter pierFace */

/* 588 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 590 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 592 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter endDist */

/* 594 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 596 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 598 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 600 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 602 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 604 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndDistanceMeasurementType */

/* 606 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 608 */	NdrFcLong( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x12 ),	/* 18 */
/* 614 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 616 */	NdrFcShort( 0x6 ),	/* 6 */
/* 618 */	NdrFcShort( 0x22 ),	/* 34 */
/* 620 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 622 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 632 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 634 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 636 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 638 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 640 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 642 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 644 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 646 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 648 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndDistanceMeasurementType */

/* 650 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 652 */	NdrFcLong( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x13 ),	/* 19 */
/* 658 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 660 */	NdrFcShort( 0xc ),	/* 12 */
/* 662 */	NdrFcShort( 0x8 ),	/* 8 */
/* 664 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 666 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 676 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 678 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 680 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 682 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 684 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 686 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 690 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndDistanceMeasurementLocation */

/* 694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x14 ),	/* 20 */
/* 702 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 704 */	NdrFcShort( 0x6 ),	/* 6 */
/* 706 */	NdrFcShort( 0x22 ),	/* 34 */
/* 708 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 710 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 720 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 722 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 724 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 726 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 728 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 730 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 732 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 734 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 736 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndDistanceMeasurementLocation */

/* 738 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 740 */	NdrFcLong( 0x0 ),	/* 0 */
/* 744 */	NdrFcShort( 0x15 ),	/* 21 */
/* 746 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 748 */	NdrFcShort( 0xc ),	/* 12 */
/* 750 */	NdrFcShort( 0x8 ),	/* 8 */
/* 752 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 754 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 764 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 766 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 768 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter measure */

/* 770 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 772 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 774 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 778 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AlignmentPoint */

/* 782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 788 */	NdrFcShort( 0x16 ),	/* 22 */
/* 790 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 796 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 798 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppPoint */

/* 808 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 810 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 812 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 814 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 816 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 818 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BridgePoint */

/* 820 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 822 */	NdrFcLong( 0x0 ),	/* 0 */
/* 826 */	NdrFcShort( 0x17 ),	/* 23 */
/* 828 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x8 ),	/* 8 */
/* 834 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 836 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 844 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppPoint */

/* 846 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 848 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 850 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LeftPoint */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x18 ),	/* 24 */
/* 866 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 874 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppPoint */

/* 884 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 886 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 888 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 890 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 892 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 894 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RightPoint */

/* 896 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 898 */	NdrFcLong( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0x19 ),	/* 25 */
/* 904 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 912 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x0 ),	/* 0 */
/* 920 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppPoint */

/* 922 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 924 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 926 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 928 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 930 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 932 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Centerline */

/* 934 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 940 */	NdrFcShort( 0x1a ),	/* 26 */
/* 942 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 946 */	NdrFcShort( 0x8 ),	/* 8 */
/* 948 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 950 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 958 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppLine */

/* 960 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 962 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 964 */	NdrFcShort( 0x7c ),	/* Type Offset=124 */

	/* Return value */

/* 966 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 968 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetBearingOffset */

/* 972 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 974 */	NdrFcLong( 0x0 ),	/* 0 */
/* 978 */	NdrFcShort( 0x1b ),	/* 27 */
/* 980 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 982 */	NdrFcShort( 0x6 ),	/* 6 */
/* 984 */	NdrFcShort( 0x2c ),	/* 44 */
/* 986 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 988 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 990 */	NdrFcShort( 0x0 ),	/* 0 */
/* 992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 994 */	NdrFcShort( 0x0 ),	/* 0 */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierFace */

/* 998 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1000 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1002 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter direction */

/* 1004 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1006 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1008 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter brgOffset */

/* 1010 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1012 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1014 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1016 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1018 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 1022 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1024 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1028 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1030 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1036 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1038 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppenum */

/* 1048 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1050 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1052 */	NdrFcShort( 0x92 ),	/* Type Offset=146 */

	/* Return value */

/* 1054 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1056 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 1060 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1062 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1068 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 1070 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1072 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1074 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 1076 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1084 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 1086 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1088 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter rgelt */

/* 1092 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1094 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1096 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Parameter pceltFetched */

/* 1098 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 1100 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1102 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1104 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1106 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reset */

/* 1110 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1112 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1116 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1118 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1124 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1126 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1136 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1138 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1140 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Skip */

/* 1142 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1148 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1150 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1154 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1156 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1158 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1166 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 1168 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1170 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1176 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 1180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1186 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1188 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1194 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1196 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1204 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter retval */

/* 1206 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1208 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1210 */	NdrFcShort( 0xac ),	/* Type Offset=172 */

	/* Return value */

/* 1212 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1214 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PierLine */

/* 1218 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1224 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1226 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1228 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1232 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1234 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1242 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter index */

/* 1244 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1246 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1248 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1250 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1252 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1254 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 1256 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1258 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GirderLineID */


	/* Procedure get_GirderLineID */


	/* Procedure get_AlignmentID */


	/* Procedure get_Count */

/* 1262 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1268 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1270 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1276 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1278 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1286 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter ID */


	/* Parameter count */

/* 1288 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1290 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1292 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 1294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1296 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PierLineIndex */

/* 1300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1306 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1308 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1312 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1314 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1316 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pier */

/* 1326 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1328 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1330 */	NdrFcShort( 0x4c ),	/* Type Offset=76 */

	/* Parameter index */

/* 1332 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1334 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1336 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 1338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1340 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__EnumPiers */

/* 1344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1352 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1358 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1360 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enumPiers */

/* 1370 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1372 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1374 */	NdrFcShort( 0x92 ),	/* Type Offset=146 */

	/* Return value */

/* 1376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1378 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindPierLine */

/* 1382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1388 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1390 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1392 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1396 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 1398 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pierID */

/* 1408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1410 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1412 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1414 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1416 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1418 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 1420 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1422 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 1426 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1428 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1432 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1434 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1438 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1440 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1442 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1450 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBridge */

/* 1452 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1454 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1456 */	NdrFcShort( 0xc2 ),	/* Type Offset=194 */

	/* Parameter pPaths */

/* 1458 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1460 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1462 */	NdrFcShort( 0xd4 ),	/* Type Offset=212 */

	/* Return value */

/* 1464 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1466 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1468 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */

/* 1470 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1472 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1476 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1478 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1482 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1484 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1486 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 1496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1498 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AlignmentID */


	/* Procedure put_AlignmentID */


	/* Procedure put_LayoutLineID */

/* 1502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1508 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1510 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1512 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1516 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1518 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1526 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter ID */


	/* Parameter ID */

/* 1528 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1530 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1532 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1534 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1536 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AlignmentID */


	/* Procedure get_AlignmentID */


	/* Procedure get_LayoutLineID */

/* 1540 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1542 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1548 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1552 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1554 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1556 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1564 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter ID */


	/* Parameter ID */

/* 1566 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1568 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1570 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1574 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BridgeAlignmentID */


	/* Procedure put_LayoutLineIDInc */

/* 1578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1584 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1586 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1588 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1592 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1594 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter inc */

/* 1604 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1606 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1608 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1610 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1612 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LayoutLineCount */

/* 1616 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1618 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1622 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1624 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1626 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1630 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1632 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nLayoutLines */

/* 1642 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1644 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1646 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 1648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1650 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LayoutLineCount */

/* 1654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0xa ),	/* 10 */
/* 1662 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1666 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1668 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1670 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1678 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nLayoutLines */

/* 1680 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1682 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1684 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 1686 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1688 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AlignmentOffset */


	/* Procedure get_Offset */

/* 1692 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1694 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1698 */	NdrFcShort( 0xb ),	/* 11 */
/* 1700 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1704 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1706 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1708 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1716 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter offset */


	/* Parameter offset */

/* 1718 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1720 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1722 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1724 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1726 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1728 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Offset */

/* 1730 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1732 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1736 */	NdrFcShort( 0xc ),	/* 12 */
/* 1738 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1740 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1742 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1744 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1746 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1754 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter offset */

/* 1756 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1758 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1760 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1762 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1764 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1766 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartSpacingOffset */


	/* Procedure get_OffsetIncrement */

/* 1768 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1770 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1774 */	NdrFcShort( 0xd ),	/* 13 */
/* 1776 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1780 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1782 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1784 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1792 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter inc */

/* 1794 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1796 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1798 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1800 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1802 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1804 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartSpacingOffset */


	/* Procedure put_OffsetIncrement */

/* 1806 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1808 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1812 */	NdrFcShort( 0xe ),	/* 14 */
/* 1814 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1816 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1818 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1820 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1822 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1830 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter newVal */


	/* Parameter inc */

/* 1832 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1834 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1836 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1838 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1840 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LayoutLineCount */


	/* Procedure get_AlignmentID */

/* 1844 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1850 */	NdrFcShort( 0xf ),	/* 15 */
/* 1852 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1856 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1858 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1860 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter ID */

/* 1870 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1872 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1874 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 1876 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1878 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1880 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AlignmentID */

/* 1882 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1888 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1890 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1892 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1896 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1898 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 1908 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1910 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1912 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 1914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1916 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddPath */

/* 1920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1926 */	NdrFcShort( 0x5 ),	/* 5 */
/* 1928 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 1930 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1932 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1934 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 1936 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1942 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1944 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 1946 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1948 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1950 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter path */

/* 1952 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1954 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 1956 */	NdrFcShort( 0xe6 ),	/* Type Offset=230 */

	/* Return value */

/* 1958 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1960 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1962 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_GirderLineID */


	/* Procedure put_GirderLineID */


	/* Procedure put_AlignmentID */

/* 1964 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1966 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1970 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1972 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 1974 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1976 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1978 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1980 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1988 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter ID */

/* 1990 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1992 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 1994 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 1996 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1998 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GirderLineIDInc */


	/* Procedure get_LayoutLineID */


	/* Procedure get_StartPierID */

/* 2002 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2004 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2008 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2010 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2014 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2016 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2018 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2026 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 2028 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2030 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2032 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2034 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2036 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2038 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_GirderLineIDInc */


	/* Procedure put_LayoutLineID */


	/* Procedure put_StartPierID */

/* 2040 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2042 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2048 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2050 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2052 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2054 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2056 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2062 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2064 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 2066 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2068 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2070 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2072 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2074 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2076 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DiaphragmLineID */


	/* Procedure put_LeftLayoutLineID */


	/* Procedure put_EndPierID */

/* 2078 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2080 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2084 */	NdrFcShort( 0xa ),	/* 10 */
/* 2086 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2088 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2090 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2092 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2094 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2098 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2102 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 2104 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2106 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2108 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2110 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2112 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DiaphragmLineID */


	/* Procedure get_DiaphragmLineID */


	/* Procedure get_RightLayoutLineID */


	/* Procedure get_StartPierID */


	/* Procedure get_PierIDInc */

/* 2116 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2118 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2122 */	NdrFcShort( 0xb ),	/* 11 */
/* 2124 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2128 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2130 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2132 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2140 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 2142 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2144 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2146 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 2148 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2150 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2152 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DiaphragmLineID */


	/* Procedure put_DiaphragmLineID */


	/* Procedure put_RightLayoutLineID */


	/* Procedure put_StartPierID */


	/* Procedure put_PierIDInc */

/* 2154 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2156 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2160 */	NdrFcShort( 0xc ),	/* 12 */
/* 2162 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2164 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2166 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2168 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2170 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 2180 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2182 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2184 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 2186 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2188 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndSpacingOffset */

/* 2192 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2198 */	NdrFcShort( 0xf ),	/* 15 */
/* 2200 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2204 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2206 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2208 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2216 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2218 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2220 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2222 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2224 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2226 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndSpacingOffset */

/* 2230 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2236 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2238 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2240 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2244 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2246 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2254 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter newVal */

/* 2256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2258 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2260 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 2262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2264 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartSpacing */

/* 2268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2274 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2276 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2282 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2284 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2294 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2296 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2298 */	NdrFcShort( 0xf8 ),	/* Type Offset=248 */

	/* Return value */

/* 2300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2302 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartSpacing */

/* 2306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2312 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2314 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2320 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2322 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2330 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2332 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2334 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2336 */	NdrFcShort( 0xfc ),	/* Type Offset=252 */

	/* Return value */

/* 2338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2340 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndSpacing */

/* 2344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2350 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2352 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2358 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2360 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2370 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2372 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2374 */	NdrFcShort( 0xf8 ),	/* Type Offset=248 */

	/* Return value */

/* 2376 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2378 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2380 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndSpacing */

/* 2382 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2384 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2388 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2390 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2396 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2398 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2408 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2410 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2412 */	NdrFcShort( 0xfc ),	/* Type Offset=252 */

	/* Return value */

/* 2414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2416 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RightGirderLineID */


	/* Procedure put_LayoutLineID */

/* 2420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2426 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2428 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2430 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2434 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2436 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter ID */

/* 2446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2448 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2450 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2452 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2454 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2456 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GirderLineCount */


	/* Procedure get_RightGirderLineID */


	/* Procedure get_LayoutLineID */

/* 2458 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2460 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2464 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2466 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2470 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2472 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2474 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2482 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter ID */


	/* Parameter ID */

/* 2484 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2486 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2488 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2490 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2492 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2494 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LayoutLineIDInc */

/* 2496 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2498 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2502 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2504 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2506 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2508 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2510 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2512 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2520 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inc */

/* 2522 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2524 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2526 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 2528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2530 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LayoutLineIDInc */

/* 2534 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2540 */	NdrFcShort( 0x18 ),	/* 24 */
/* 2542 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2546 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2548 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2550 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2558 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter inc */

/* 2560 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2562 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2564 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 2566 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2568 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2570 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 2572 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2574 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2578 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2580 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 2582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2586 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2588 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2596 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBridge */

/* 2598 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2600 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2602 */	NdrFcShort( 0xc2 ),	/* Type Offset=194 */

	/* Parameter ppArrayGirderLines */

/* 2604 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2606 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2608 */	NdrFcShort( 0x10e ),	/* Type Offset=270 */

	/* Return value */

/* 2610 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2612 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 2616 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2618 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2622 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2624 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2628 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2630 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2632 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2640 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2642 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2644 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2646 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 2648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2650 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */

/* 2654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2660 */	NdrFcShort( 0xa ),	/* 10 */
/* 2662 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2664 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2668 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2670 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2678 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2680 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2682 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2684 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2686 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2688 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DiaphragmLineIDInc */


	/* Procedure get_LayoutLineIDInc */


	/* Procedure get_EndPierID */

/* 2692 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2694 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2698 */	NdrFcShort( 0xd ),	/* 13 */
/* 2700 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2704 */	NdrFcShort( 0x2c ),	/* 44 */
/* 2706 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2708 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2716 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */


	/* Parameter pVal */

/* 2718 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2720 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2722 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2724 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2726 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2728 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_DiaphragmLineIDInc */


	/* Procedure put_LayoutLineIDInc */


	/* Procedure put_EndPierID */

/* 2730 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2732 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2736 */	NdrFcShort( 0xe ),	/* 14 */
/* 2738 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2740 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2742 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2744 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2746 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2754 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */


	/* Parameter newVal */

/* 2756 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2758 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2760 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2762 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2764 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2766 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */


	/* Procedure get_StartMeasurementType */

/* 2768 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2770 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2774 */	NdrFcShort( 0xf ),	/* 15 */
/* 2776 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2780 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2782 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2784 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2792 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 2794 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2796 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2798 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */


	/* Return value */

/* 2800 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2802 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2804 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Type */


	/* Procedure put_StartMeasurementType */

/* 2806 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2808 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2812 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2814 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2816 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2818 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2820 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2822 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2830 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 2832 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2834 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2836 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 2838 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2840 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartMeasurementLocation */

/* 2844 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2850 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2852 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2856 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2858 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2860 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2868 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2870 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2872 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2874 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 2876 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2878 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2880 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartMeasurementLocation */

/* 2882 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2884 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2888 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2890 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2892 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2894 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2896 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2898 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2908 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2910 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2912 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2916 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndMeasurementType */

/* 2920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2926 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2928 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2932 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2934 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2936 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2942 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2944 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 2946 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2948 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2950 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 2952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2954 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndMeasurementType */

/* 2958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2964 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2966 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 2968 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2972 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2974 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2982 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 2984 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2986 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 2988 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2990 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2992 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 2994 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndMeasurementLocation */

/* 2996 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2998 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3002 */	NdrFcShort( 0x15 ),	/* 21 */
/* 3004 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3008 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3010 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3012 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3022 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3024 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3026 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 3028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3030 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndMeasurementLocation */

/* 3034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3040 */	NdrFcShort( 0x16 ),	/* 22 */
/* 3042 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3044 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3048 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3050 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3056 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3058 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3060 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3062 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3064 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3066 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3068 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3070 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartPierID */

/* 3072 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3074 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3078 */	NdrFcShort( 0x11 ),	/* 17 */
/* 3080 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3084 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3086 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3088 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3096 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3098 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3100 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3102 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 3104 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3106 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3108 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartPierID */

/* 3110 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3112 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3116 */	NdrFcShort( 0x12 ),	/* 18 */
/* 3118 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3120 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3122 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3124 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3126 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3134 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3136 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3138 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3140 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 3142 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3144 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3146 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PierLineCount */


	/* Procedure get_EndPierID */

/* 3148 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3150 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3154 */	NdrFcShort( 0x13 ),	/* 19 */
/* 3156 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3158 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3160 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3162 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3164 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3172 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 3174 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3176 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3178 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 3180 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3182 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3184 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndPierID */

/* 3186 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3188 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3192 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3194 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3196 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3198 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3200 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3202 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3210 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3212 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3214 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3216 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 3218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3220 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PierIDInc */

/* 3224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3230 */	NdrFcShort( 0x15 ),	/* 21 */
/* 3232 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3236 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3238 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3240 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3248 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3250 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3252 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3254 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 3256 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3258 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PierIDInc */

/* 3262 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3264 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3268 */	NdrFcShort( 0x16 ),	/* 22 */
/* 3270 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3272 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3274 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3276 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3278 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3286 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3288 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3290 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3292 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 3294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3296 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Continuous */

/* 3300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3306 */	NdrFcShort( 0x17 ),	/* 23 */
/* 3308 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3312 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3314 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3316 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbContinuous */

/* 3326 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3328 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3330 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 3332 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3334 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Continuous */

/* 3338 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3340 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3344 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3346 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3348 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3352 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3354 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3362 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bContinuous */

/* 3364 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3366 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3368 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 3370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3372 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartMeasurementType */

/* 3376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3382 */	NdrFcShort( 0x19 ),	/* 25 */
/* 3384 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3388 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3390 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3392 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3402 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3404 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3406 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 3408 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3410 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartMeasurementType */

/* 3414 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3416 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3420 */	NdrFcShort( 0x1a ),	/* 26 */
/* 3422 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3424 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3426 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3428 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3430 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3432 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3438 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3440 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3442 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3444 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3446 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3448 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3450 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartMeasurementLocation */

/* 3452 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3454 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3458 */	NdrFcShort( 0x1b ),	/* 27 */
/* 3460 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3464 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3466 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3468 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3476 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3478 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3480 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3482 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 3484 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3486 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3488 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartMeasurementLocation */

/* 3490 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3492 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3496 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3498 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3500 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3504 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3506 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3514 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3516 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3518 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3520 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3522 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3524 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndMeasurementType */

/* 3528 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3530 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3534 */	NdrFcShort( 0x1d ),	/* 29 */
/* 3536 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3540 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3542 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3544 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3552 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3554 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3556 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3558 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 3560 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3562 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3564 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndMeasurementType */

/* 3566 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3568 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3572 */	NdrFcShort( 0x1e ),	/* 30 */
/* 3574 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3576 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3580 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3582 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3590 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3592 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3594 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3596 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3598 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3600 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndMeasurementLocation */

/* 3604 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3606 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3610 */	NdrFcShort( 0x1f ),	/* 31 */
/* 3612 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3616 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3618 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3620 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3628 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3630 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3632 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3634 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 3636 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3638 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndMeasurementLocation */

/* 3642 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3644 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3648 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3650 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3652 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3654 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3656 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3658 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3666 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter newVal */

/* 3668 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3670 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3672 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 3674 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3676 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3678 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartPier */

/* 3680 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3682 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3686 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3688 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3694 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3696 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3704 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3706 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3708 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3710 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 3712 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3714 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndPier */

/* 3718 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3720 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3724 */	NdrFcShort( 0x5 ),	/* 5 */
/* 3726 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3730 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3732 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3734 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3742 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 3744 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3746 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3748 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */

	/* Return value */

/* 3750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3752 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_GirderLength */

/* 3756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3762 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3764 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3768 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3770 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3772 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3778 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3780 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pLength */

/* 3782 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3784 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3786 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 3788 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3790 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3792 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SpanLength */

/* 3794 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3796 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3800 */	NdrFcShort( 0x7 ),	/* 7 */
/* 3802 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3806 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3808 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3810 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3814 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3818 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pLength */

/* 3820 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3822 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3824 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 3826 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3828 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3830 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StartStation */


	/* Procedure get_Station */


	/* Procedure get_LayoutLength */

/* 3832 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3834 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3840 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3842 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3844 */	NdrFcShort( 0x2c ),	/* 44 */
/* 3846 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 3848 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pStation */


	/* Parameter pStation */


	/* Parameter pLength */

/* 3858 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 3860 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3862 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 3864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3866 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PierPoint */

/* 3870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3876 */	NdrFcShort( 0x9 ),	/* 9 */
/* 3878 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 3880 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3884 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3886 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3892 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3894 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */

/* 3896 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3898 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3900 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppPoint */

/* 3902 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3904 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3906 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 3908 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3910 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3912 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BearingPoint */

/* 3914 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3916 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3920 */	NdrFcShort( 0xa ),	/* 10 */
/* 3922 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 3924 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3926 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3928 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3930 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3932 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3934 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3938 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */

/* 3940 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3942 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3944 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppPoint */

/* 3946 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3948 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3950 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 3952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3954 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 3956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndPoint */

/* 3958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3964 */	NdrFcShort( 0xb ),	/* 11 */
/* 3966 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 3968 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3972 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3974 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3982 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */

/* 3984 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3986 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 3988 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppPoint */

/* 3990 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3992 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 3994 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 3996 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3998 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetEndPoints */

/* 4002 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4004 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4008 */	NdrFcShort( 0xc ),	/* 12 */
/* 4010 */	NdrFcShort( 0x40 ),	/* X64 Stack size/offset = 64 */
/* 4012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4016 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x7,		/* 7 */
/* 4018 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4020 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4024 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4026 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pntPier1 */

/* 4028 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4030 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4032 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Parameter pntEnd1 */

/* 4034 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4036 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4038 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Parameter pntBrg1 */

/* 4040 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4042 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4044 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Parameter pntBrg2 */

/* 4046 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4048 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 4050 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Parameter pntEnd2 */

/* 4052 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4054 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 4056 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Parameter pntPier2 */

/* 4058 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4060 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 4062 */	NdrFcShort( 0x66 ),	/* Type Offset=102 */

	/* Return value */

/* 4064 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4066 */	NdrFcShort( 0x38 ),	/* X64 Stack size/offset = 56 */
/* 4068 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Path */

/* 4070 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4072 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4076 */	NdrFcShort( 0xd ),	/* 13 */
/* 4078 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4082 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4084 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4086 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4094 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 4096 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4098 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4100 */	NdrFcShort( 0x128 ),	/* Type Offset=296 */

	/* Return value */

/* 4102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4104 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Direction */

/* 4108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4114 */	NdrFcShort( 0xe ),	/* 14 */
/* 4116 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4122 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4124 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4132 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDirection */

/* 4134 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4136 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4138 */	NdrFcShort( 0x13e ),	/* Type Offset=318 */

	/* Return value */

/* 4140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4142 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BearingOffset */

/* 4146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4152 */	NdrFcShort( 0xf ),	/* 15 */
/* 4154 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 4156 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4158 */	NdrFcShort( 0x2c ),	/* 44 */
/* 4160 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 4162 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4170 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */

/* 4172 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4174 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4176 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pBrgOffset */

/* 4178 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4180 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4182 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 4184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4186 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 4190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4196 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4198 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 4200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4204 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 4206 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBridge */

/* 4216 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4218 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4220 */	NdrFcShort( 0x154 ),	/* Type Offset=340 */

	/* Parameter ppArrayDiaphagmLines */

/* 4222 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4224 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4226 */	NdrFcShort( 0x166 ),	/* Type Offset=358 */

	/* Return value */

/* 4228 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4230 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StartStation */


	/* Procedure put_Station */

/* 4234 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4236 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4240 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4242 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4244 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4246 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4248 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4250 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4258 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter station */


	/* Parameter station */

/* 4260 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4262 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4264 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 4266 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4268 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4270 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Orientation */

/* 4272 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4274 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4278 */	NdrFcShort( 0x9 ),	/* 9 */
/* 4280 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4286 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4288 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4292 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4296 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter orientation */

/* 4298 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4300 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4302 */	NdrFcShort( 0x196 ),	/* Type Offset=406 */

	/* Return value */

/* 4304 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4306 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4308 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Orientation */

/* 4310 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4312 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4316 */	NdrFcShort( 0xa ),	/* 10 */
/* 4318 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4322 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4324 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4326 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4328 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter orientation */

/* 4336 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4338 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4340 */	NdrFcShort( 0x1a8 ),	/* Type Offset=424 */

	/* Return value */

/* 4342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4344 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Staggered */

/* 4348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4354 */	NdrFcShort( 0xd ),	/* 13 */
/* 4356 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4358 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4360 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4362 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4364 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4372 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 4374 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4376 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4378 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4380 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4382 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Staggered */

/* 4386 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4388 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4392 */	NdrFcShort( 0xe ),	/* 14 */
/* 4394 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4398 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4400 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4402 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4406 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4410 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 4412 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4414 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4416 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4418 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4420 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RightGirderLineID */


	/* Procedure put_LeftGirderLineID */

/* 4424 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4426 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4430 */	NdrFcShort( 0xf ),	/* 15 */
/* 4432 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4434 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4438 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4440 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4448 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter ID */

/* 4450 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4452 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4454 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 4456 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4458 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RightGirderLineID */


	/* Procedure get_LeftGirderLineID */

/* 4462 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4464 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4468 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4470 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4474 */	NdrFcShort( 0x2c ),	/* 44 */
/* 4476 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4478 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4486 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */


	/* Parameter ID */

/* 4488 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4490 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4492 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 4494 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4496 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4498 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_RightGirderLineID */

/* 4500 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4502 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4506 */	NdrFcShort( 0x11 ),	/* 17 */
/* 4508 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4510 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4512 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4514 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4516 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 4526 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4528 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4530 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 4532 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4534 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4536 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RightGirderLineID */

/* 4538 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4540 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4544 */	NdrFcShort( 0x12 ),	/* 18 */
/* 4546 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4550 */	NdrFcShort( 0x2c ),	/* 44 */
/* 4552 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4554 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4562 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 4564 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4566 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4568 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 4570 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4572 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Point */

/* 4576 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4578 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4582 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4584 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4590 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4592 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4594 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4600 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter point */

/* 4602 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4604 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4606 */	NdrFcShort( 0x1b2 ),	/* Type Offset=434 */

	/* Return value */

/* 4608 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4610 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4612 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Point */

/* 4614 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4616 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4620 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4622 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4628 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4630 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4632 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4638 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter point */

/* 4640 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4642 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4644 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Return value */

/* 4646 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4648 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Direction */

/* 4652 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4654 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4658 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4660 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4666 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4668 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter direction */

/* 4678 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4680 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4682 */	NdrFcShort( 0x1c8 ),	/* Type Offset=456 */

	/* Return value */

/* 4684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4686 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Direction */

/* 4690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4696 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4698 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4702 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4704 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4706 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4714 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter direction */

/* 4716 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4718 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4720 */	NdrFcShort( 0x1da ),	/* Type Offset=474 */

	/* Return value */

/* 4722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4724 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Staggered */

/* 4728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4734 */	NdrFcShort( 0xb ),	/* 11 */
/* 4736 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4738 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4742 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4744 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 4754 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4756 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4758 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4762 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Staggered */

/* 4766 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4772 */	NdrFcShort( 0xc ),	/* 12 */
/* 4774 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4778 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4780 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4782 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4786 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4790 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 4792 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4794 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4796 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4798 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4800 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4802 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LeftGirderLineID */

/* 4804 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4806 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4810 */	NdrFcShort( 0xd ),	/* 13 */
/* 4812 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4814 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4818 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4820 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4828 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 4830 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4832 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4834 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 4836 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4838 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LeftGirderLineID */

/* 4842 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4844 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4848 */	NdrFcShort( 0xe ),	/* 14 */
/* 4850 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4854 */	NdrFcShort( 0x2c ),	/* 44 */
/* 4856 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4858 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4866 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 4868 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4870 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4872 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 4874 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4876 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4878 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EndStation */

/* 4880 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4882 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4886 */	NdrFcShort( 0x9 ),	/* 9 */
/* 4888 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4890 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4894 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4896 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4904 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter station */

/* 4906 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4908 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4910 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 4912 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4914 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4916 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EndStation */

/* 4918 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4920 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4924 */	NdrFcShort( 0xa ),	/* 10 */
/* 4926 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4930 */	NdrFcShort( 0x2c ),	/* 44 */
/* 4932 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4934 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4942 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pStation */

/* 4944 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4946 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4948 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 4950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4952 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Divisor */

/* 4956 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4962 */	NdrFcShort( 0xf ),	/* 15 */
/* 4964 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 4966 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4970 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4972 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4974 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4980 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter divisor */

/* 4982 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4984 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 4986 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4988 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4990 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 4992 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Divisor */

/* 4994 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4996 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5000 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5002 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5006 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5008 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5010 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5018 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter divisor */

/* 5020 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5022 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5024 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5026 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5028 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Staggered */

/* 5032 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5034 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5038 */	NdrFcShort( 0x11 ),	/* 17 */
/* 5040 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5042 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5046 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5048 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5050 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5056 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 5058 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5060 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5062 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5064 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5066 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5068 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Staggered */

/* 5070 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5072 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5076 */	NdrFcShort( 0x12 ),	/* 18 */
/* 5078 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5082 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5084 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5086 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5088 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5094 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bStaggered */

/* 5096 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5098 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5100 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5102 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5104 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LeftGirderLineID */

/* 5108 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5114 */	NdrFcShort( 0x13 ),	/* 19 */
/* 5116 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5118 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5122 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5124 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5132 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 5134 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5136 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5138 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5142 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LeftGirderLineID */

/* 5146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5152 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5154 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5158 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5160 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5162 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5170 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 5172 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5174 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5176 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5180 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Length */

/* 5184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5190 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5192 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5194 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5196 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5198 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5200 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5204 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5208 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gdrLineID */

/* 5210 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5212 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5214 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter pLength */

/* 5216 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5218 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5220 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 5222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5224 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Point */

/* 5228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5234 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5236 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5238 */	NdrFcShort( 0x16 ),	/* 22 */
/* 5240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5242 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 5244 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter gdrLineID */

/* 5254 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5256 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5258 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter endType */

/* 5260 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5262 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5264 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppPoint */

/* 5266 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5268 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5270 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Return value */

/* 5272 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5274 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5276 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Perimeter */

/* 5278 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5280 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5284 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5286 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5288 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5290 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5292 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 5294 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5296 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5298 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5302 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nMinPointsPerSide */

/* 5304 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5306 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5308 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter points */

/* 5310 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5312 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5314 */	NdrFcShort( 0x1de ),	/* Type Offset=478 */

	/* Return value */

/* 5316 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5318 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PerimeterEx */

/* 5322 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5328 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5330 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 5332 */	NdrFcShort( 0x30 ),	/* 48 */
/* 5334 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5336 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x5,		/* 5 */
/* 5338 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5344 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5346 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nMinPointsPerSide */

/* 5348 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5350 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5352 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter startPierID */

/* 5354 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5356 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5358 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter endPierID */

/* 5360 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5362 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5364 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter points */

/* 5366 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5368 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5370 */	NdrFcShort( 0x1de ),	/* Type Offset=478 */

	/* Return value */

/* 5372 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5374 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TransverseEdgePoints */

/* 5378 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5380 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5384 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5386 */	NdrFcShort( 0x38 ),	/* X64 Stack size/offset = 56 */
/* 5388 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5390 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5392 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x6,		/* 6 */
/* 5394 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5402 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter endType */

/* 5404 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5406 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5408 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppLeft */

/* 5410 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5412 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5414 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Parameter ppLeftBreak */

/* 5416 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5418 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5420 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Parameter ppRightBreak */

/* 5422 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5424 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5426 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Parameter ppRight */

/* 5428 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5430 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5432 */	NdrFcShort( 0x1c4 ),	/* Type Offset=452 */

	/* Return value */

/* 5434 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5436 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 5438 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EdgePath */

/* 5440 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5442 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5446 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5448 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5450 */	NdrFcShort( 0xc ),	/* 12 */
/* 5452 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5454 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 5456 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter side */

/* 5466 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5468 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5470 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter vbLayoutPath */

/* 5472 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5474 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5476 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter path */

/* 5478 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5480 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5482 */	NdrFcShort( 0x1f4 ),	/* Type Offset=500 */

	/* Return value */

/* 5484 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5486 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5488 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Create */

/* 5490 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5492 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5496 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5498 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5502 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5504 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5506 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5512 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5514 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBridge */

/* 5516 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5518 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5520 */	NdrFcShort( 0x154 ),	/* Type Offset=340 */

	/* Parameter ppDeckBoundary */

/* 5522 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5524 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5526 */	NdrFcShort( 0x20a ),	/* Type Offset=522 */

	/* Return value */

/* 5528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5530 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TransverseEdgeID */

/* 5534 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5540 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5542 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5544 */	NdrFcShort( 0x16 ),	/* 22 */
/* 5546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5548 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5550 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5556 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5558 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5560 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5562 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5564 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5566 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5568 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5570 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5574 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TransverseEdgeID */

/* 5578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5584 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5586 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5588 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5590 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5592 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5594 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5602 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5604 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5606 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5608 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5610 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5612 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5614 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5616 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5618 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5620 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TransverseEdgeType */

/* 5622 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5624 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5628 */	NdrFcShort( 0x7 ),	/* 7 */
/* 5630 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5632 */	NdrFcShort( 0xc ),	/* 12 */
/* 5634 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5636 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5638 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5640 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5646 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5648 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5650 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5652 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter edgeType */

/* 5654 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5656 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5658 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 5660 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5662 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TransverseEdgeType */

/* 5666 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5672 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5674 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5676 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5678 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5680 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5682 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5692 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5694 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5696 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter edgeType */

/* 5698 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 5700 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5702 */	NdrFcShort( 0x62 ),	/* Type Offset=98 */

	/* Return value */

/* 5704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5706 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EdgeID */

/* 5710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5716 */	NdrFcShort( 0x9 ),	/* 9 */
/* 5718 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5720 */	NdrFcShort( 0x16 ),	/* 22 */
/* 5722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5724 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5726 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5734 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter side */

/* 5736 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5738 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5740 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5742 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5744 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5746 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5748 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5750 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5752 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EdgeID */

/* 5754 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5756 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5760 */	NdrFcShort( 0xa ),	/* 10 */
/* 5762 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5764 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5766 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5768 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5770 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5778 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter side */

/* 5780 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5782 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5784 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5786 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5788 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5790 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5794 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EdgeBreakID */

/* 5798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5804 */	NdrFcShort( 0xb ),	/* 11 */
/* 5806 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5808 */	NdrFcShort( 0x16 ),	/* 22 */
/* 5810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5812 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5814 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter side */

/* 5824 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5826 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5828 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5830 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5832 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5834 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5836 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5838 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5840 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EdgeBreakID */

/* 5842 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5844 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5848 */	NdrFcShort( 0xc ),	/* 12 */
/* 5850 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5852 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5854 */	NdrFcShort( 0x2c ),	/* 44 */
/* 5856 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5858 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5860 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5866 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter side */

/* 5868 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5870 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5872 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ID */

/* 5874 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5876 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5878 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 5880 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5882 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5884 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_BreakEdge */

/* 5886 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5888 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5892 */	NdrFcShort( 0xd ),	/* 13 */
/* 5894 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5896 */	NdrFcShort( 0x12 ),	/* 18 */
/* 5898 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5900 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 5902 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5906 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5910 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5912 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5914 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5916 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter side */

/* 5918 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5920 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5922 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bBreak */

/* 5924 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5926 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5928 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5930 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5932 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5934 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BreakEdge */

/* 5936 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5938 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5942 */	NdrFcShort( 0xe ),	/* 14 */
/* 5944 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 5946 */	NdrFcShort( 0xc ),	/* 12 */
/* 5948 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5950 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 5952 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5954 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5958 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5960 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter end */

/* 5962 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5964 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 5966 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter side */

/* 5968 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5970 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 5972 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bBreak */

/* 5974 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5976 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5978 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5980 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5982 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 5984 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_CogoModel */

/* 5986 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5988 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5992 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5994 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 5996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5998 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6000 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6002 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6004 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6010 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pCogoModel */

/* 6012 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6014 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6016 */	NdrFcShort( 0x220 ),	/* Type Offset=544 */

	/* Return value */

/* 6018 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6020 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6022 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CogoModel */

/* 6024 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6026 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6030 */	NdrFcShort( 0x4 ),	/* 4 */
/* 6032 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6036 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6038 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6040 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6048 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pCogoModel */

/* 6050 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6052 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6054 */	NdrFcShort( 0x232 ),	/* Type Offset=562 */

	/* Return value */

/* 6056 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6058 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_Alignment */

/* 6062 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6064 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6068 */	NdrFcShort( 0x5 ),	/* 5 */
/* 6070 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6072 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6074 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6076 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 6078 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6086 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6088 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6090 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6092 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter pAligment */

/* 6094 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6096 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6098 */	NdrFcShort( 0x236 ),	/* Type Offset=566 */

	/* Return value */

/* 6100 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6102 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Alignment */

/* 6106 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6112 */	NdrFcShort( 0x6 ),	/* 6 */
/* 6114 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6116 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6120 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6122 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6128 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6130 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6132 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6134 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6136 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter pAlignment */

/* 6138 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6140 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6142 */	NdrFcShort( 0x248 ),	/* Type Offset=584 */

	/* Return value */

/* 6144 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6146 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6148 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BridgeAlignment */

/* 6150 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6152 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6156 */	NdrFcShort( 0x9 ),	/* 9 */
/* 6158 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6160 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6162 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6164 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6166 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6170 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6174 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter alignment */

/* 6176 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6178 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6180 */	NdrFcShort( 0x248 ),	/* Type Offset=584 */

	/* Return value */

/* 6182 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6184 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AlignmentOffset */

/* 6188 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6194 */	NdrFcShort( 0xa ),	/* 10 */
/* 6196 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6198 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6202 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6204 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6206 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6212 */	NdrFcShort( 0x8 ),	/* 8 */

	/* Parameter offset */

/* 6214 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6216 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6218 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 6220 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6222 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6224 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BridgeLine */

/* 6226 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6228 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6232 */	NdrFcShort( 0xc ),	/* 12 */
/* 6234 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6236 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6240 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6242 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bridgeLine */

/* 6252 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6254 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6256 */	NdrFcShort( 0x24c ),	/* Type Offset=588 */

	/* Return value */

/* 6258 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6260 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateLayoutLines */

/* 6264 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6270 */	NdrFcShort( 0xd ),	/* 13 */
/* 6272 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6276 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6278 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6280 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6288 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFactory */

/* 6290 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6292 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6294 */	NdrFcShort( 0x250 ),	/* Type Offset=592 */

	/* Return value */

/* 6296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6298 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindLayoutLine */

/* 6302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6308 */	NdrFcShort( 0xe ),	/* 14 */
/* 6310 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6312 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6314 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6316 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6318 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6326 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6328 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6330 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6332 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter path */

/* 6334 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6336 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6338 */	NdrFcShort( 0x128 ),	/* Type Offset=296 */

	/* Return value */

/* 6340 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6342 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreatePierLine */

/* 6346 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6352 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6354 */	NdrFcShort( 0x48 ),	/* X64 Stack size/offset = 72 */
/* 6356 */	NdrFcShort( 0x40 ),	/* 64 */
/* 6358 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6360 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 6362 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big amd64 byval param */
/* 6364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6366 */	NdrFcShort( 0x1 ),	/* 1 */
/* 6368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6370 */	NdrFcShort( 0x2800 ),	/* 10240 */

	/* Parameter ID */

/* 6372 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6374 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6376 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter alignmentID */

/* 6378 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6380 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6382 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter station */

/* 6384 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 6386 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6388 */	NdrFcShort( 0x62a ),	/* Type Offset=1578 */

	/* Parameter orientation */

/* 6390 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 6392 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6394 */	NdrFcShort( 0x196 ),	/* Type Offset=406 */

	/* Parameter width */

/* 6396 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6398 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 6400 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter offset */

/* 6402 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6404 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 6406 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter ppPier */

/* 6408 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6410 */	NdrFcShort( 0x38 ),	/* X64 Stack size/offset = 56 */
/* 6412 */	NdrFcShort( 0x634 ),	/* Type Offset=1588 */

	/* Return value */

/* 6414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6416 */	NdrFcShort( 0x40 ),	/* X64 Stack size/offset = 64 */
/* 6418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPierLine */

/* 6420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6426 */	NdrFcShort( 0x11 ),	/* 17 */
/* 6428 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6430 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6434 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6436 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idx */

/* 6446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6448 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6450 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter ppPier */

/* 6452 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6454 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6456 */	NdrFcShort( 0x634 ),	/* Type Offset=1588 */

	/* Return value */

/* 6458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6460 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindPierLine */

/* 6464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6470 */	NdrFcShort( 0x12 ),	/* 18 */
/* 6472 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6474 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6478 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6480 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6490 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6492 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6494 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter ppPier */

/* 6496 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6498 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6500 */	NdrFcShort( 0x634 ),	/* Type Offset=1588 */

	/* Return value */

/* 6502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6504 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateGirderLines */

/* 6508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6514 */	NdrFcShort( 0x14 ),	/* 20 */
/* 6516 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6520 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6522 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6524 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6532 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFactory */

/* 6534 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6536 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6538 */	NdrFcShort( 0x64a ),	/* Type Offset=1610 */

	/* Return value */

/* 6540 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6542 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindGirderLine */

/* 6546 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6548 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6552 */	NdrFcShort( 0x15 ),	/* 21 */
/* 6554 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6556 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6558 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6560 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6562 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6570 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6572 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6574 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6576 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter ppGirderLine */

/* 6578 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6580 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6582 */	NdrFcShort( 0x65c ),	/* Type Offset=1628 */

	/* Return value */

/* 6584 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6586 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6588 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateDiaphragmLines */

/* 6590 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6592 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6596 */	NdrFcShort( 0x17 ),	/* 23 */
/* 6598 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6602 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6604 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6606 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6614 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFactory */

/* 6616 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6618 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6620 */	NdrFcShort( 0x672 ),	/* Type Offset=1650 */

	/* Return value */

/* 6622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6624 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure FindDiaphragmLine */

/* 6628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6634 */	NdrFcShort( 0x18 ),	/* 24 */
/* 6636 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 6638 */	NdrFcShort( 0x10 ),	/* 16 */
/* 6640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6642 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6644 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6652 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ID */

/* 6654 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6656 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6658 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter ppDiaphragmLine */

/* 6660 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6662 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6664 */	NdrFcShort( 0x684 ),	/* Type Offset=1668 */

	/* Return value */

/* 6666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6668 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DiaphragmLineCount */

/* 6672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6678 */	NdrFcShort( 0x19 ),	/* 25 */
/* 6680 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6684 */	NdrFcShort( 0x2c ),	/* 44 */
/* 6686 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6688 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6696 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pVal */

/* 6698 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6700 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6702 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 6704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6706 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateDeckBoundary */

/* 6710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6716 */	NdrFcShort( 0x1a ),	/* 26 */
/* 6718 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6724 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 6726 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6734 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pFactory */

/* 6736 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 6738 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6740 */	NdrFcShort( 0x69a ),	/* Type Offset=1690 */

	/* Return value */

/* 6742 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6744 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6746 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DeckBoundary */

/* 6748 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6750 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6754 */	NdrFcShort( 0x1b ),	/* 27 */
/* 6756 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 6758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6760 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6762 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6764 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6772 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDeckBoundary */

/* 6774 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6776 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6778 */	NdrFcShort( 0x6ac ),	/* Type Offset=1708 */

	/* Return value */

/* 6780 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6782 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UpdateGeometry */

/* 6786 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6788 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6792 */	NdrFcShort( 0x1c ),	/* 28 */
/* 6794 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 6796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6798 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6800 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 6802 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6810 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 6812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6814 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 6816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const WBFLBridgeGeometry_MIDL_TYPE_FORMAT_STRING WBFLBridgeGeometry__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0x337799ad ),	/* 863476141 */
/* 16 */	NdrFcShort( 0x766c ),	/* 30316 */
/* 18 */	NdrFcShort( 0x4fb7 ),	/* 20407 */
/* 20 */	0xa2,		/* 162 */
			0x38,		/* 56 */
/* 22 */	0x9a,		/* 154 */
			0x4c,		/* 76 */
/* 24 */	0x61,		/* 97 */
			0xff,		/* 255 */
/* 26 */	0xbe,		/* 190 */
			0x29,		/* 41 */
/* 28 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 30 */	NdrFcShort( 0x2 ),	/* Offset= 2 (32) */
/* 32 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 34 */	NdrFcLong( 0x2c98a251 ),	/* 748200529 */
/* 38 */	NdrFcShort( 0x55f7 ),	/* 22007 */
/* 40 */	NdrFcShort( 0x11d5 ),	/* 4565 */
/* 42 */	0x8c,		/* 140 */
			0x29,		/* 41 */
/* 44 */	0x0,		/* 0 */
			0x60,		/* 96 */
/* 46 */	0x97,		/* 151 */
			0xc6,		/* 198 */
/* 48 */	0x8a,		/* 138 */
			0x9c,		/* 156 */
/* 50 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 52 */	NdrFcShort( 0x2 ),	/* Offset= 2 (54) */
/* 54 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 56 */	NdrFcLong( 0x2c98a246 ),	/* 748200518 */
/* 60 */	NdrFcShort( 0x55f7 ),	/* 22007 */
/* 62 */	NdrFcShort( 0x11d5 ),	/* 4565 */
/* 64 */	0x8c,		/* 140 */
			0x29,		/* 41 */
/* 66 */	0x0,		/* 0 */
			0x60,		/* 96 */
/* 68 */	0x97,		/* 151 */
			0xc6,		/* 198 */
/* 70 */	0x8a,		/* 138 */
			0x9c,		/* 156 */
/* 72 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 74 */	NdrFcShort( 0x2 ),	/* Offset= 2 (76) */
/* 76 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 78 */	NdrFcLong( 0x4086070 ),	/* 67657840 */
/* 82 */	NdrFcShort( 0x2a58 ),	/* 10840 */
/* 84 */	NdrFcShort( 0x4557 ),	/* 17751 */
/* 86 */	0xa3,		/* 163 */
			0x20,		/* 32 */
/* 88 */	0x64,		/* 100 */
			0x9c,		/* 156 */
/* 90 */	0x61,		/* 97 */
			0x56,		/* 86 */
/* 92 */	0x52,		/* 82 */
			0xfa,		/* 250 */
/* 94 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 96 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 98 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 100 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 102 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 104 */	NdrFcShort( 0x2 ),	/* Offset= 2 (106) */
/* 106 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 108 */	NdrFcLong( 0x55b8ef96 ),	/* 1438183318 */
/* 112 */	NdrFcShort( 0xfadf ),	/* -1313 */
/* 114 */	NdrFcShort( 0x11d2 ),	/* 4562 */
/* 116 */	0x8c,		/* 140 */
			0xdf,		/* 223 */
/* 118 */	0x98,		/* 152 */
			0x49,		/* 73 */
/* 120 */	0xc7,		/* 199 */
			0xc,		/* 12 */
/* 122 */	0xc7,		/* 199 */
			0x34,		/* 52 */
/* 124 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 126 */	NdrFcShort( 0x2 ),	/* Offset= 2 (128) */
/* 128 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 130 */	NdrFcLong( 0x54a873e0 ),	/* 1420325856 */
/* 134 */	NdrFcShort( 0xfce2 ),	/* -798 */
/* 136 */	NdrFcShort( 0x11d2 ),	/* 4562 */
/* 138 */	0x8c,		/* 140 */
			0xdf,		/* 223 */
/* 140 */	0xb2,		/* 178 */
			0x32,		/* 50 */
/* 142 */	0x10,		/* 16 */
			0x1,		/* 1 */
/* 144 */	0x16,		/* 22 */
			0x34,		/* 52 */
/* 146 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 148 */	NdrFcShort( 0x2 ),	/* Offset= 2 (150) */
/* 150 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 152 */	NdrFcLong( 0x2a1a7ae0 ),	/* 706378464 */
/* 156 */	NdrFcShort( 0xb7e1 ),	/* -18463 */
/* 158 */	NdrFcShort( 0x46b7 ),	/* 18103 */
/* 160 */	0xa4,		/* 164 */
			0xa7,		/* 167 */
/* 162 */	0x25,		/* 37 */
			0x32,		/* 50 */
/* 164 */	0xf9,		/* 249 */
			0x2f,		/* 47 */
/* 166 */	0x12,		/* 18 */
			0x46,		/* 70 */
/* 168 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 170 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 172 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 174 */	NdrFcShort( 0x2 ),	/* Offset= 2 (176) */
/* 176 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 186 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 188 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 190 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 192 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 194 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 196 */	NdrFcLong( 0xcf09fa44 ),	/* -821429692 */
/* 200 */	NdrFcShort( 0x1095 ),	/* 4245 */
/* 202 */	NdrFcShort( 0x4f63 ),	/* 20323 */
/* 204 */	0xb3,		/* 179 */
			0xdb,		/* 219 */
/* 206 */	0xc4,		/* 196 */
			0xba,		/* 186 */
/* 208 */	0x86,		/* 134 */
			0x17,		/* 23 */
/* 210 */	0xa9,		/* 169 */
			0x8e,		/* 142 */
/* 212 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 214 */	NdrFcLong( 0xdfdf1c35 ),	/* -539026379 */
/* 218 */	NdrFcShort( 0x39db ),	/* 14811 */
/* 220 */	NdrFcShort( 0x4285 ),	/* 17029 */
/* 222 */	0xaa,		/* 170 */
			0x38,		/* 56 */
/* 224 */	0xbe,		/* 190 */
			0x6c,		/* 108 */
/* 226 */	0x18,		/* 24 */
			0x9e,		/* 158 */
/* 228 */	0x29,		/* 41 */
			0xe0,		/* 224 */
/* 230 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 232 */	NdrFcLong( 0xa43dace9 ),	/* -1539461911 */
/* 236 */	NdrFcShort( 0x956a ),	/* -27286 */
/* 238 */	NdrFcShort( 0x4421 ),	/* 17441 */
/* 240 */	0x9a,		/* 154 */
			0x3a,		/* 58 */
/* 242 */	0x1,		/* 1 */
			0xd2,		/* 210 */
/* 244 */	0x45,		/* 69 */
			0x3f,		/* 63 */
/* 246 */	0xce,		/* 206 */
			0x3,		/* 3 */
/* 248 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 250 */	NdrFcShort( 0x2 ),	/* Offset= 2 (252) */
/* 252 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 254 */	NdrFcLong( 0xcaba1f9a ),	/* -893771878 */
/* 258 */	NdrFcShort( 0xcee0 ),	/* -12576 */
/* 260 */	NdrFcShort( 0x40e6 ),	/* 16614 */
/* 262 */	0x91,		/* 145 */
			0xca,		/* 202 */
/* 264 */	0x18,		/* 24 */
			0xd3,		/* 211 */
/* 266 */	0xf4,		/* 244 */
			0xfc,		/* 252 */
/* 268 */	0x7,		/* 7 */
			0x18,		/* 24 */
/* 270 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 272 */	NdrFcShort( 0x2 ),	/* Offset= 2 (274) */
/* 274 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 276 */	NdrFcLong( 0xf7e15329 ),	/* -136228055 */
/* 280 */	NdrFcShort( 0x3f3b ),	/* 16187 */
/* 282 */	NdrFcShort( 0x4161 ),	/* 16737 */
/* 284 */	0x9c,		/* 156 */
			0x9c,		/* 156 */
/* 286 */	0x43,		/* 67 */
			0xed,		/* 237 */
/* 288 */	0x3f,		/* 63 */
			0x9b,		/* 155 */
/* 290 */	0x68,		/* 104 */
			0x9c,		/* 156 */
/* 292 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 294 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 296 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 298 */	NdrFcShort( 0x2 ),	/* Offset= 2 (300) */
/* 300 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 302 */	NdrFcLong( 0xa43dace9 ),	/* -1539461911 */
/* 306 */	NdrFcShort( 0x956a ),	/* -27286 */
/* 308 */	NdrFcShort( 0x4421 ),	/* 17441 */
/* 310 */	0x9a,		/* 154 */
			0x3a,		/* 58 */
/* 312 */	0x1,		/* 1 */
			0xd2,		/* 210 */
/* 314 */	0x45,		/* 69 */
			0x3f,		/* 63 */
/* 316 */	0xce,		/* 206 */
			0x3,		/* 3 */
/* 318 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 320 */	NdrFcShort( 0x2 ),	/* Offset= 2 (322) */
/* 322 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 324 */	NdrFcLong( 0x2c98a251 ),	/* 748200529 */
/* 328 */	NdrFcShort( 0x55f7 ),	/* 22007 */
/* 330 */	NdrFcShort( 0x11d5 ),	/* 4565 */
/* 332 */	0x8c,		/* 140 */
			0x29,		/* 41 */
/* 334 */	0x0,		/* 0 */
			0x60,		/* 96 */
/* 336 */	0x97,		/* 151 */
			0xc6,		/* 198 */
/* 338 */	0x8a,		/* 138 */
			0x9c,		/* 156 */
/* 340 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 342 */	NdrFcLong( 0xcf09fa44 ),	/* -821429692 */
/* 346 */	NdrFcShort( 0x1095 ),	/* 4245 */
/* 348 */	NdrFcShort( 0x4f63 ),	/* 20323 */
/* 350 */	0xb3,		/* 179 */
			0xdb,		/* 219 */
/* 352 */	0xc4,		/* 196 */
			0xba,		/* 186 */
/* 354 */	0x86,		/* 134 */
			0x17,		/* 23 */
/* 356 */	0xa9,		/* 169 */
			0x8e,		/* 142 */
/* 358 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 360 */	NdrFcShort( 0x2 ),	/* Offset= 2 (362) */
/* 362 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 364 */	NdrFcLong( 0xf7e15329 ),	/* -136228055 */
/* 368 */	NdrFcShort( 0x3f3b ),	/* 16187 */
/* 370 */	NdrFcShort( 0x4161 ),	/* 16737 */
/* 372 */	0x9c,		/* 156 */
			0x9c,		/* 156 */
/* 374 */	0x43,		/* 67 */
			0xed,		/* 237 */
/* 376 */	0x3f,		/* 63 */
			0x9b,		/* 155 */
/* 378 */	0x68,		/* 104 */
			0x9c,		/* 156 */
/* 380 */	
			0x12, 0x0,	/* FC_UP */
/* 382 */	NdrFcShort( 0xe ),	/* Offset= 14 (396) */
/* 384 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 386 */	NdrFcShort( 0x2 ),	/* 2 */
/* 388 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 390 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 392 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 394 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 396 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 398 */	NdrFcShort( 0x8 ),	/* 8 */
/* 400 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (384) */
/* 402 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 404 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 406 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x8 ),	/* 8 */
/* 412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0xffde ),	/* Offset= -34 (380) */
/* 416 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 418 */	NdrFcShort( 0x6 ),	/* Offset= 6 (424) */
/* 420 */	
			0x13, 0x0,	/* FC_OP */
/* 422 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (396) */
/* 424 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x8 ),	/* 8 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 432 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (420) */
/* 434 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 436 */	NdrFcLong( 0x55b8ef96 ),	/* 1438183318 */
/* 440 */	NdrFcShort( 0xfadf ),	/* -1313 */
/* 442 */	NdrFcShort( 0x11d2 ),	/* 4562 */
/* 444 */	0x8c,		/* 140 */
			0xdf,		/* 223 */
/* 446 */	0x98,		/* 152 */
			0x49,		/* 73 */
/* 448 */	0xc7,		/* 199 */
			0xc,		/* 12 */
/* 450 */	0xc7,		/* 199 */
			0x34,		/* 52 */
/* 452 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 454 */	NdrFcShort( 0xffec ),	/* Offset= -20 (434) */
/* 456 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 458 */	NdrFcLong( 0x2c98a251 ),	/* 748200529 */
/* 462 */	NdrFcShort( 0x55f7 ),	/* 22007 */
/* 464 */	NdrFcShort( 0x11d5 ),	/* 4565 */
/* 466 */	0x8c,		/* 140 */
			0x29,		/* 41 */
/* 468 */	0x0,		/* 0 */
			0x60,		/* 96 */
/* 470 */	0x97,		/* 151 */
			0xc6,		/* 198 */
/* 472 */	0x8a,		/* 138 */
			0x9c,		/* 156 */
/* 474 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 476 */	NdrFcShort( 0xffec ),	/* Offset= -20 (456) */
/* 478 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 480 */	NdrFcShort( 0x2 ),	/* Offset= 2 (482) */
/* 482 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 484 */	NdrFcLong( 0xb0d56fa3 ),	/* -1328189533 */
/* 488 */	NdrFcShort( 0xc8d6 ),	/* -14122 */
/* 490 */	NdrFcShort( 0x11d2 ),	/* 4562 */
/* 492 */	0x8c,		/* 140 */
			0xdf,		/* 223 */
/* 494 */	0xc5,		/* 197 */
			0x5c,		/* 92 */
/* 496 */	0x1c,		/* 28 */
			0xa8,		/* 168 */
/* 498 */	0x4a,		/* 74 */
			0x34,		/* 52 */
/* 500 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 502 */	NdrFcShort( 0x2 ),	/* Offset= 2 (504) */
/* 504 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 506 */	NdrFcLong( 0xa43dace9 ),	/* -1539461911 */
/* 510 */	NdrFcShort( 0x956a ),	/* -27286 */
/* 512 */	NdrFcShort( 0x4421 ),	/* 17441 */
/* 514 */	0x9a,		/* 154 */
			0x3a,		/* 58 */
/* 516 */	0x1,		/* 1 */
			0xd2,		/* 210 */
/* 518 */	0x45,		/* 69 */
			0x3f,		/* 63 */
/* 520 */	0xce,		/* 206 */
			0x3,		/* 3 */
/* 522 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 524 */	NdrFcShort( 0x2 ),	/* Offset= 2 (526) */
/* 526 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 528 */	NdrFcLong( 0x8fc6de2c ),	/* -1882792404 */
/* 532 */	NdrFcShort( 0x969d ),	/* -26979 */
/* 534 */	NdrFcShort( 0x4f74 ),	/* 20340 */
/* 536 */	0xbd,		/* 189 */
			0x77,		/* 119 */
/* 538 */	0x93,		/* 147 */
			0x55,		/* 85 */
/* 540 */	0xc1,		/* 193 */
			0xc4,		/* 196 */
/* 542 */	0xbe,		/* 190 */
			0xb6,		/* 182 */
/* 544 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 546 */	NdrFcLong( 0xb9e4933c ),	/* -1176202436 */
/* 550 */	NdrFcShort( 0x5e73 ),	/* 24179 */
/* 552 */	NdrFcShort( 0x11d5 ),	/* 4565 */
/* 554 */	0x8c,		/* 140 */
			0x32,		/* 50 */
/* 556 */	0x0,		/* 0 */
			0x60,		/* 96 */
/* 558 */	0x97,		/* 151 */
			0xc6,		/* 198 */
/* 560 */	0x8a,		/* 138 */
			0x9c,		/* 156 */
/* 562 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 564 */	NdrFcShort( 0xffec ),	/* Offset= -20 (544) */
/* 566 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 568 */	NdrFcLong( 0x30638cfa ),	/* 811830522 */
/* 572 */	NdrFcShort( 0xf23 ),	/* 3875 */
/* 574 */	NdrFcShort( 0x4784 ),	/* 18308 */
/* 576 */	0x8f,		/* 143 */
			0xc9,		/* 201 */
/* 578 */	0xd1,		/* 209 */
			0xa2,		/* 162 */
/* 580 */	0xe4,		/* 228 */
			0xa5,		/* 165 */
/* 582 */	0xf,		/* 15 */
			0x2,		/* 2 */
/* 584 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 586 */	NdrFcShort( 0xffec ),	/* Offset= -20 (566) */
/* 588 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 590 */	NdrFcShort( 0xfe98 ),	/* Offset= -360 (230) */
/* 592 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 594 */	NdrFcLong( 0xd58bbf23 ),	/* -712261853 */
/* 598 */	NdrFcShort( 0xb486 ),	/* -19322 */
/* 600 */	NdrFcShort( 0x417e ),	/* 16766 */
/* 602 */	0xb5,		/* 181 */
			0x5c,		/* 92 */
/* 604 */	0x63,		/* 99 */
			0xd1,		/* 209 */
/* 606 */	0x81,		/* 129 */
			0x6,		/* 6 */
/* 608 */	0x89,		/* 137 */
			0x47,		/* 71 */
/* 610 */	
			0x11, 0x0,	/* FC_RP */
/* 612 */	NdrFcShort( 0x3c6 ),	/* Offset= 966 (1578) */
/* 614 */	
			0x12, 0x0,	/* FC_UP */
/* 616 */	NdrFcShort( 0x3ae ),	/* Offset= 942 (1558) */
/* 618 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 620 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 622 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 624 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 626 */	NdrFcShort( 0x2 ),	/* Offset= 2 (628) */
/* 628 */	NdrFcShort( 0x10 ),	/* 16 */
/* 630 */	NdrFcShort( 0x2f ),	/* 47 */
/* 632 */	NdrFcLong( 0x14 ),	/* 20 */
/* 636 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 638 */	NdrFcLong( 0x3 ),	/* 3 */
/* 642 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 644 */	NdrFcLong( 0x11 ),	/* 17 */
/* 648 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 650 */	NdrFcLong( 0x2 ),	/* 2 */
/* 654 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 656 */	NdrFcLong( 0x4 ),	/* 4 */
/* 660 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 662 */	NdrFcLong( 0x5 ),	/* 5 */
/* 666 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 668 */	NdrFcLong( 0xb ),	/* 11 */
/* 672 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 674 */	NdrFcLong( 0xa ),	/* 10 */
/* 678 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 680 */	NdrFcLong( 0x6 ),	/* 6 */
/* 684 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (916) */
/* 686 */	NdrFcLong( 0x7 ),	/* 7 */
/* 690 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 692 */	NdrFcLong( 0x8 ),	/* 8 */
/* 696 */	NdrFcShort( 0xfec4 ),	/* Offset= -316 (380) */
/* 698 */	NdrFcLong( 0xd ),	/* 13 */
/* 702 */	NdrFcShort( 0xdc ),	/* Offset= 220 (922) */
/* 704 */	NdrFcLong( 0x9 ),	/* 9 */
/* 708 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (940) */
/* 710 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 714 */	NdrFcShort( 0xf4 ),	/* Offset= 244 (958) */
/* 716 */	NdrFcLong( 0x24 ),	/* 36 */
/* 720 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (1484) */
/* 722 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 726 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1484) */
/* 728 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 732 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (1488) */
/* 734 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 738 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (1492) */
/* 740 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 744 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (1496) */
/* 746 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 750 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (1500) */
/* 752 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 756 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (1504) */
/* 758 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 762 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (1508) */
/* 764 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 768 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (1492) */
/* 770 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 774 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1496) */
/* 776 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 780 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (1512) */
/* 782 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 786 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1508) */
/* 788 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 792 */	NdrFcShort( 0x2d4 ),	/* Offset= 724 (1516) */
/* 794 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 798 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1520) */
/* 800 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 804 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (1524) */
/* 806 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 810 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (1528) */
/* 812 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 816 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (1532) */
/* 818 */	NdrFcLong( 0x10 ),	/* 16 */
/* 822 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 824 */	NdrFcLong( 0x12 ),	/* 18 */
/* 828 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 830 */	NdrFcLong( 0x13 ),	/* 19 */
/* 834 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 836 */	NdrFcLong( 0x15 ),	/* 21 */
/* 840 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 842 */	NdrFcLong( 0x16 ),	/* 22 */
/* 846 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 848 */	NdrFcLong( 0x17 ),	/* 23 */
/* 852 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 854 */	NdrFcLong( 0xe ),	/* 14 */
/* 858 */	NdrFcShort( 0x2aa ),	/* Offset= 682 (1540) */
/* 860 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 864 */	NdrFcShort( 0x2ae ),	/* Offset= 686 (1550) */
/* 866 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 870 */	NdrFcShort( 0x2ac ),	/* Offset= 684 (1554) */
/* 872 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 876 */	NdrFcShort( 0x268 ),	/* Offset= 616 (1492) */
/* 878 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 882 */	NdrFcShort( 0x266 ),	/* Offset= 614 (1496) */
/* 884 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 888 */	NdrFcShort( 0x264 ),	/* Offset= 612 (1500) */
/* 890 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 894 */	NdrFcShort( 0x25a ),	/* Offset= 602 (1496) */
/* 896 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 900 */	NdrFcShort( 0x254 ),	/* Offset= 596 (1496) */
/* 902 */	NdrFcLong( 0x0 ),	/* 0 */
/* 906 */	NdrFcShort( 0x0 ),	/* Offset= 0 (906) */
/* 908 */	NdrFcLong( 0x1 ),	/* 1 */
/* 912 */	NdrFcShort( 0x0 ),	/* Offset= 0 (912) */
/* 914 */	NdrFcShort( 0xffff ),	/* Offset= -1 (913) */
/* 916 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 922 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 924 */	NdrFcLong( 0x0 ),	/* 0 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 934 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 936 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 938 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 940 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 942 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 950 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 952 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 954 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 956 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 958 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 960 */	NdrFcShort( 0x2 ),	/* Offset= 2 (962) */
/* 962 */	
			0x12, 0x0,	/* FC_UP */
/* 964 */	NdrFcShort( 0x1f6 ),	/* Offset= 502 (1466) */
/* 966 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 968 */	NdrFcShort( 0x20 ),	/* 32 */
/* 970 */	NdrFcShort( 0xa ),	/* 10 */
/* 972 */	NdrFcLong( 0x8 ),	/* 8 */
/* 976 */	NdrFcShort( 0x50 ),	/* Offset= 80 (1056) */
/* 978 */	NdrFcLong( 0xd ),	/* 13 */
/* 982 */	NdrFcShort( 0x82 ),	/* Offset= 130 (1112) */
/* 984 */	NdrFcLong( 0x9 ),	/* 9 */
/* 988 */	NdrFcShort( 0xa2 ),	/* Offset= 162 (1150) */
/* 990 */	NdrFcLong( 0xc ),	/* 12 */
/* 994 */	NdrFcShort( 0xc2 ),	/* Offset= 194 (1188) */
/* 996 */	NdrFcLong( 0x24 ),	/* 36 */
/* 1000 */	NdrFcShort( 0x114 ),	/* Offset= 276 (1276) */
/* 1002 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 1006 */	NdrFcShort( 0x130 ),	/* Offset= 304 (1310) */
/* 1008 */	NdrFcLong( 0x10 ),	/* 16 */
/* 1012 */	NdrFcShort( 0x14a ),	/* Offset= 330 (1342) */
/* 1014 */	NdrFcLong( 0x2 ),	/* 2 */
/* 1018 */	NdrFcShort( 0x160 ),	/* Offset= 352 (1370) */
/* 1020 */	NdrFcLong( 0x3 ),	/* 3 */
/* 1024 */	NdrFcShort( 0x176 ),	/* Offset= 374 (1398) */
/* 1026 */	NdrFcLong( 0x14 ),	/* 20 */
/* 1030 */	NdrFcShort( 0x18c ),	/* Offset= 396 (1426) */
/* 1032 */	NdrFcShort( 0xffff ),	/* Offset= -1 (1031) */
/* 1034 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1038 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1042 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1044 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1048 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1050 */	
			0x12, 0x0,	/* FC_UP */
/* 1052 */	NdrFcShort( 0xfd70 ),	/* Offset= -656 (396) */
/* 1054 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1056 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1058 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1068) */
/* 1064 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1066 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1068 */	
			0x11, 0x0,	/* FC_RP */
/* 1070 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1034) */
/* 1072 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1074 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1082 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1084 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1086 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1088 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 1090 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1092 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1094 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1100 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1104 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1106 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1108 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1072) */
/* 1110 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1112 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1114 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1118 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1124) */
/* 1120 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1122 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1124 */	
			0x11, 0x0,	/* FC_RP */
/* 1126 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1090) */
/* 1128 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1132 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1136 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1138 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1142 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1144 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1146 */	NdrFcShort( 0xff32 ),	/* Offset= -206 (940) */
/* 1148 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1150 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1152 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1156 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1162) */
/* 1158 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1160 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1162 */	
			0x11, 0x0,	/* FC_RP */
/* 1164 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1128) */
/* 1166 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1170 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1174 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1176 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1180 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1182 */	
			0x12, 0x0,	/* FC_UP */
/* 1184 */	NdrFcShort( 0x176 ),	/* Offset= 374 (1558) */
/* 1186 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1188 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1190 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1194 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1200) */
/* 1196 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1198 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1200 */	
			0x11, 0x0,	/* FC_RP */
/* 1202 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1166) */
/* 1204 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1206 */	NdrFcLong( 0x2f ),	/* 47 */
/* 1210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1214 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1216 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1218 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1220 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 1222 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1224 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1226 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1228 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1230 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1232 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1234 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1236 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1238 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1240 */	NdrFcShort( 0xa ),	/* Offset= 10 (1250) */
/* 1242 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1244 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1246 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (1204) */
/* 1248 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1250 */	
			0x12, 0x0,	/* FC_UP */
/* 1252 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (1222) */
/* 1254 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1258 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1262 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1264 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1268 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1270 */	
			0x12, 0x0,	/* FC_UP */
/* 1272 */	NdrFcShort( 0xffda ),	/* Offset= -38 (1234) */
/* 1274 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1276 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1278 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1282 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1288) */
/* 1284 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1286 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1288 */	
			0x11, 0x0,	/* FC_RP */
/* 1290 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1254) */
/* 1292 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 1294 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1296 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1298 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1300 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1302 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 1304 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1306 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (1292) */
			0x5b,		/* FC_END */
/* 1310 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1312 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1316 */	NdrFcShort( 0xa ),	/* Offset= 10 (1326) */
/* 1318 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1320 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1322 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (1298) */
			0x5b,		/* FC_END */
/* 1326 */	
			0x11, 0x0,	/* FC_RP */
/* 1328 */	NdrFcShort( 0xff12 ),	/* Offset= -238 (1090) */
/* 1330 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1332 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1334 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1338 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1340 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1342 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1344 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1348 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1354) */
/* 1350 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1352 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1354 */	
			0x12, 0x0,	/* FC_UP */
/* 1356 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1330) */
/* 1358 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 1360 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1362 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1366 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1368 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 1370 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1372 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1376 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1382) */
/* 1378 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1380 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1382 */	
			0x12, 0x0,	/* FC_UP */
/* 1384 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1358) */
/* 1386 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1388 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1390 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1394 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1396 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 1398 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1400 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1404 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1410) */
/* 1406 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1408 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1410 */	
			0x12, 0x0,	/* FC_UP */
/* 1412 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1386) */
/* 1414 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 1416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1418 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1422 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1424 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1426 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1428 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1432 */	NdrFcShort( 0x6 ),	/* Offset= 6 (1438) */
/* 1434 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 1436 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 1438 */	
			0x12, 0x0,	/* FC_UP */
/* 1440 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (1414) */
/* 1442 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 1444 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1446 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1448 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1450 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1452 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1454 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1456 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 1458 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1460 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1462 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1442) */
/* 1464 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1466 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1468 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1470 */	NdrFcShort( 0xffec ),	/* Offset= -20 (1450) */
/* 1472 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1472) */
/* 1474 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1476 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1478 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1480 */	0x0,		/* 0 */
			NdrFcShort( 0xfdfd ),	/* Offset= -515 (966) */
			0x5b,		/* FC_END */
/* 1484 */	
			0x12, 0x0,	/* FC_UP */
/* 1486 */	NdrFcShort( 0xff04 ),	/* Offset= -252 (1234) */
/* 1488 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1490 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 1492 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1494 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1496 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1498 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1500 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1502 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 1504 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1506 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1508 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1510 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1512 */	
			0x12, 0x0,	/* FC_UP */
/* 1514 */	NdrFcShort( 0xfdaa ),	/* Offset= -598 (916) */
/* 1516 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1518 */	NdrFcShort( 0xfb8e ),	/* Offset= -1138 (380) */
/* 1520 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1522 */	NdrFcShort( 0xfe3e ),	/* Offset= -450 (1072) */
/* 1524 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1526 */	NdrFcShort( 0xfdb6 ),	/* Offset= -586 (940) */
/* 1528 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1530 */	NdrFcShort( 0xfdc4 ),	/* Offset= -572 (958) */
/* 1532 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 1534 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1536) */
/* 1536 */	
			0x12, 0x0,	/* FC_UP */
/* 1538 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1558) */
/* 1540 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1542 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1544 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1546 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1548 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1550 */	
			0x12, 0x0,	/* FC_UP */
/* 1552 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1540) */
/* 1554 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1556 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1558 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1560 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1564 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1564) */
/* 1566 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1568 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1570 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1572 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1574 */	NdrFcShort( 0xfc44 ),	/* Offset= -956 (618) */
/* 1576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1578 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1582 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1586 */	NdrFcShort( 0xfc34 ),	/* Offset= -972 (614) */
/* 1588 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1590 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1592) */
/* 1592 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1594 */	NdrFcLong( 0x4086070 ),	/* 67657840 */
/* 1598 */	NdrFcShort( 0x2a58 ),	/* 10840 */
/* 1600 */	NdrFcShort( 0x4557 ),	/* 17751 */
/* 1602 */	0xa3,		/* 163 */
			0x20,		/* 32 */
/* 1604 */	0x64,		/* 100 */
			0x9c,		/* 156 */
/* 1606 */	0x61,		/* 97 */
			0x56,		/* 86 */
/* 1608 */	0x52,		/* 82 */
			0xfa,		/* 250 */
/* 1610 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1612 */	NdrFcLong( 0xf7a4b484 ),	/* -140200828 */
/* 1616 */	NdrFcShort( 0x4c6b ),	/* 19563 */
/* 1618 */	NdrFcShort( 0x4a36 ),	/* 18998 */
/* 1620 */	0xb6,		/* 182 */
			0x2c,		/* 44 */
/* 1622 */	0xfc,		/* 252 */
			0x21,		/* 33 */
/* 1624 */	0x6f,		/* 111 */
			0x9,		/* 9 */
/* 1626 */	0xf0,		/* 240 */
			0x33,		/* 51 */
/* 1628 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1630 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1632) */
/* 1632 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1634 */	NdrFcLong( 0xedd54a64 ),	/* -304788892 */
/* 1638 */	NdrFcShort( 0x4f63 ),	/* 20323 */
/* 1640 */	NdrFcShort( 0x4dc0 ),	/* 19904 */
/* 1642 */	0xb6,		/* 182 */
			0x5,		/* 5 */
/* 1644 */	0xda,		/* 218 */
			0xa4,		/* 164 */
/* 1646 */	0xc6,		/* 198 */
			0x3b,		/* 59 */
/* 1648 */	0xda,		/* 218 */
			0x64,		/* 100 */
/* 1650 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1652 */	NdrFcLong( 0xb3979762 ),	/* -1281910942 */
/* 1656 */	NdrFcShort( 0xe72a ),	/* -6358 */
/* 1658 */	NdrFcShort( 0x401b ),	/* 16411 */
/* 1660 */	0xac,		/* 172 */
			0x3,		/* 3 */
/* 1662 */	0x28,		/* 40 */
			0xe9,		/* 233 */
/* 1664 */	0x53,		/* 83 */
			0xa2,		/* 162 */
/* 1666 */	0x22,		/* 34 */
			0xc2,		/* 194 */
/* 1668 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1670 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1672) */
/* 1672 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1674 */	NdrFcLong( 0x24885559 ),	/* 612914521 */
/* 1678 */	NdrFcShort( 0xfabb ),	/* -1349 */
/* 1680 */	NdrFcShort( 0x4327 ),	/* 17191 */
/* 1682 */	0xb3,		/* 179 */
			0xd,		/* 13 */
/* 1684 */	0xb2,		/* 178 */
			0xee,		/* 238 */
/* 1686 */	0x5c,		/* 92 */
			0x95,		/* 149 */
/* 1688 */	0xc5,		/* 197 */
			0xc1,		/* 193 */
/* 1690 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1692 */	NdrFcLong( 0xf89d246a ),	/* -123919254 */
/* 1696 */	NdrFcShort( 0x8f7d ),	/* -28803 */
/* 1698 */	NdrFcShort( 0x4a27 ),	/* 18983 */
/* 1700 */	0xa2,		/* 162 */
			0x7e,		/* 126 */
/* 1702 */	0xdd,		/* 221 */
			0x73,		/* 115 */
/* 1704 */	0xbe,		/* 190 */
			0x33,		/* 51 */
/* 1706 */	0x20,		/* 32 */
			0x87,		/* 135 */
/* 1708 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1710 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1712) */
/* 1712 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1714 */	NdrFcLong( 0x8fc6de2c ),	/* -1882792404 */
/* 1718 */	NdrFcShort( 0x969d ),	/* -26979 */
/* 1720 */	NdrFcShort( 0x4f74 ),	/* 20340 */
/* 1722 */	0xbd,		/* 189 */
			0x77,		/* 119 */
/* 1724 */	0x93,		/* 147 */
			0x55,		/* 85 */
/* 1726 */	0xc1,		/* 193 */
			0xc4,		/* 196 */
/* 1728 */	0xbe,		/* 190 */
			0xb6,		/* 182 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Standard interface: __MIDL_itf_WBFLBridgeGeometry_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IPierLine, ver. 0.0,
   GUID={0x04086070,0x2A58,0x4557,{0xA3,0x20,0x64,0x9C,0x61,0x56,0x52,0xFA}} */

#pragma code_seg(".orpc")
static const unsigned short IPierLine_FormatStringOffsetTable[] =
    {
    0,
    38,
    76,
    114,
    152,
    190,
    228,
    266,
    304,
    342,
    386,
    430,
    474,
    518,
    562,
    606,
    650,
    694,
    738,
    782,
    820,
    858,
    896,
    934,
    972
    };

static const MIDL_STUBLESS_PROXY_INFO IPierLine_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IPierLine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPierLine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IPierLine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(28) _IPierLineProxyVtbl = 
{
    &IPierLine_ProxyInfo,
    &IID_IPierLine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPierLine::get_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Station */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Direction */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Normal */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Skew */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Index */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_ID */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_NextPierLine */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_PrevPierLine */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_BearingOffset */ ,
    (void *) (INT_PTR) -1 /* IPierLine::put_BearingOffset */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_BearingOffsetMeasurementType */ ,
    (void *) (INT_PTR) -1 /* IPierLine::put_BearingOffsetMeasurementType */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_EndDistance */ ,
    (void *) (INT_PTR) -1 /* IPierLine::put_EndDistance */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_EndDistanceMeasurementType */ ,
    (void *) (INT_PTR) -1 /* IPierLine::put_EndDistanceMeasurementType */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_EndDistanceMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* IPierLine::put_EndDistanceMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_AlignmentPoint */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_BridgePoint */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_LeftPoint */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_RightPoint */ ,
    (void *) (INT_PTR) -1 /* IPierLine::get_Centerline */ ,
    (void *) (INT_PTR) -1 /* IPierLine::GetBearingOffset */
};

const CInterfaceStubVtbl _IPierLineStubVtbl =
{
    &IID_IPierLine,
    &IPierLine_ServerInfo,
    28,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IEnumPierLines, ver. 0.0,
   GUID={0x2A1A7AE0,0xB7E1,0x46b7,{0xA4,0xA7,0x25,0x32,0xF9,0x2F,0x12,0x46}} */

#pragma code_seg(".orpc")
static const unsigned short IEnumPierLines_FormatStringOffsetTable[] =
    {
    1022,
    1060,
    1110,
    1142
    };

static const MIDL_STUBLESS_PROXY_INFO IEnumPierLines_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IEnumPierLines_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEnumPierLines_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IEnumPierLines_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IEnumPierLinesProxyVtbl = 
{
    &IEnumPierLines_ProxyInfo,
    &IID_IEnumPierLines,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IEnumPierLines::Clone */ ,
    (void *) (INT_PTR) -1 /* IEnumPierLines::Next */ ,
    (void *) (INT_PTR) -1 /* IEnumPierLines::Reset */ ,
    (void *) (INT_PTR) -1 /* IEnumPierLines::Skip */
};

const CInterfaceStubVtbl _IEnumPierLinesStubVtbl =
{
    &IID_IEnumPierLines,
    &IEnumPierLines_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IPierLineCollection, ver. 0.0,
   GUID={0xB97C82D3,0xEE60,0x4D92,{0xB9,0x99,0xE6,0xC9,0x15,0xC4,0x9F,0x83}} */

#pragma code_seg(".orpc")
static const unsigned short IPierLineCollection_FormatStringOffsetTable[] =
    {
    1180,
    1218,
    1262,
    1300,
    1344,
    1382
    };

static const MIDL_STUBLESS_PROXY_INFO IPierLineCollection_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IPierLineCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPierLineCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IPierLineCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IPierLineCollectionProxyVtbl = 
{
    &IPierLineCollection_ProxyInfo,
    &IID_IPierLineCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::get__NewEnum */ ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::get_PierLine */ ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::get_Count */ ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::get_PierLineIndex */ ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::get__EnumPiers */ ,
    (void *) (INT_PTR) -1 /* IPierLineCollection::FindPierLine */
};

const CInterfaceStubVtbl _IPierLineCollectionStubVtbl =
{
    &IID_IPierLineCollection,
    &IPierLineCollection_ServerInfo,
    9,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ILayoutLineFactory, ver. 0.0,
   GUID={0xD58BBF23,0xB486,0x417E,{0xB5,0x5C,0x63,0xD1,0x81,0x06,0x89,0x47}} */

#pragma code_seg(".orpc")
static const unsigned short ILayoutLineFactory_FormatStringOffsetTable[] =
    {
    1426,
    1470
    };

static const MIDL_STUBLESS_PROXY_INFO ILayoutLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ILayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ILayoutLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ILayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _ILayoutLineFactoryProxyVtbl = 
{
    &ILayoutLineFactory_ProxyInfo,
    &IID_ILayoutLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Reset */
};

const CInterfaceStubVtbl _ILayoutLineFactoryStubVtbl =
{
    &IID_ILayoutLineFactory,
    &ILayoutLineFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IAlignmentOffsetLayoutLineFactory, ver. 0.0,
   GUID={0x0A47CB63,0xC3CF,0x47DF,{0x8F,0x2F,0x5B,0x72,0xC8,0x3C,0x02,0xB8}} */

#pragma code_seg(".orpc")
static const unsigned short IAlignmentOffsetLayoutLineFactory_FormatStringOffsetTable[] =
    {
    1426,
    1470,
    1502,
    1540,
    1578,
    190,
    1616,
    1654,
    1692,
    1730,
    1768,
    1806,
    1844,
    1882
    };

static const MIDL_STUBLESS_PROXY_INFO IAlignmentOffsetLayoutLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IAlignmentOffsetLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAlignmentOffsetLayoutLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IAlignmentOffsetLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IAlignmentOffsetLayoutLineFactoryProxyVtbl = 
{
    &IAlignmentOffsetLayoutLineFactory_ProxyInfo,
    &IID_IAlignmentOffsetLayoutLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_LayoutLineIDInc */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_LayoutLineIDInc */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_LayoutLineCount */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_LayoutLineCount */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_Offset */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_Offset */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_OffsetIncrement */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_OffsetIncrement */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::get_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IAlignmentOffsetLayoutLineFactory::put_AlignmentID */
};

const CInterfaceStubVtbl _IAlignmentOffsetLayoutLineFactoryStubVtbl =
{
    &IID_IAlignmentOffsetLayoutLineFactory,
    &IAlignmentOffsetLayoutLineFactory_ServerInfo,
    17,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISimpleLayoutLineFactory, ver. 0.0,
   GUID={0x64CC0388,0x9A1C,0x41D3,{0x83,0x24,0xD3,0xEA,0x44,0xDC,0x6C,0xFF}} */

#pragma code_seg(".orpc")
static const unsigned short ISimpleLayoutLineFactory_FormatStringOffsetTable[] =
    {
    1426,
    1470,
    1920
    };

static const MIDL_STUBLESS_PROXY_INFO ISimpleLayoutLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISimpleLayoutLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _ISimpleLayoutLineFactoryProxyVtbl = 
{
    &ISimpleLayoutLineFactory_ProxyInfo,
    &IID_ISimpleLayoutLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* ISimpleLayoutLineFactory::AddPath */
};

const CInterfaceStubVtbl _ISimpleLayoutLineFactoryStubVtbl =
{
    &IID_ISimpleLayoutLineFactory,
    &ISimpleLayoutLineFactory_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IUniformSpacingLayoutLineFactory, ver. 0.0,
   GUID={0xB34A9D24,0x9551,0x490A,{0xA3,0xC2,0x3C,0x7C,0xF6,0x80,0x3D,0x4C}} */

#pragma code_seg(".orpc")
static const unsigned short IUniformSpacingLayoutLineFactory_FormatStringOffsetTable[] =
    {
    1426,
    1470,
    1262,
    1964,
    2002,
    2040,
    228,
    2078,
    2116,
    2154,
    1768,
    1806,
    2192,
    2230,
    2268,
    2306,
    2344,
    2382,
    2420,
    2458,
    2496,
    2534
    };

static const MIDL_STUBLESS_PROXY_INFO IUniformSpacingLayoutLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IUniformSpacingLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IUniformSpacingLayoutLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IUniformSpacingLayoutLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(25) _IUniformSpacingLayoutLineFactoryProxyVtbl = 
{
    &IUniformSpacingLayoutLineFactory_ProxyInfo,
    &IID_IUniformSpacingLayoutLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* ILayoutLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_StartPierID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_StartPierID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_EndPierID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_EndPierID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_PierIDInc */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_PierIDInc */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_StartSpacingOffset */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_StartSpacingOffset */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_EndSpacingOffset */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_EndSpacingOffset */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_StartSpacing */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_StartSpacing */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_EndSpacing */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_EndSpacing */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::put_LayoutLineIDInc */ ,
    (void *) (INT_PTR) -1 /* IUniformSpacingLayoutLineFactory::get_LayoutLineIDInc */
};

const CInterfaceStubVtbl _IUniformSpacingLayoutLineFactoryStubVtbl =
{
    &IID_IUniformSpacingLayoutLineFactory,
    &IUniformSpacingLayoutLineFactory_ServerInfo,
    25,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IGirderLineFactory, ver. 0.0,
   GUID={0xF7A4B484,0x4C6B,0x4A36,{0xB6,0x2C,0xFC,0x21,0x6F,0x09,0xF0,0x33}} */

#pragma code_seg(".orpc")
static const unsigned short IGirderLineFactory_FormatStringOffsetTable[] =
    {
    2572,
    1470
    };

static const MIDL_STUBLESS_PROXY_INFO IGirderLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGirderLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IGirderLineFactoryProxyVtbl = 
{
    &IGirderLineFactory_ProxyInfo,
    &IID_IGirderLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Reset */
};

const CInterfaceStubVtbl _IGirderLineFactoryStubVtbl =
{
    &IID_IGirderLineFactory,
    &IGirderLineFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISingleGirderLineFactory, ver. 0.0,
   GUID={0x9BE02875,0x99F1,0x4529,{0xB7,0xF7,0x12,0x35,0xDF,0x2F,0xC0,0x10}} */

#pragma code_seg(".orpc")
static const unsigned short ISingleGirderLineFactory_FormatStringOffsetTable[] =
    {
    2572,
    1470,
    1262,
    1964,
    2002,
    2040,
    2616,
    2654,
    2116,
    2154,
    2692,
    2730,
    2768,
    2806,
    2844,
    2882,
    2920,
    2958,
    2996,
    3034
    };

static const MIDL_STUBLESS_PROXY_INFO ISingleGirderLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISingleGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISingleGirderLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISingleGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(23) _ISingleGirderLineFactoryProxyVtbl = 
{
    &ISingleGirderLineFactory_ProxyInfo,
    &IID_ISingleGirderLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_GirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_GirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_LayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_Type */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_Type */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_StartPierID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_StartPierID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_EndPierID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_EndPierID */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_StartMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_StartMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_StartMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_StartMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_EndMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_EndMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::get_EndMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISingleGirderLineFactory::put_EndMeasurementLocation */
};

const CInterfaceStubVtbl _ISingleGirderLineFactoryStubVtbl =
{
    &IID_ISingleGirderLineFactory,
    &ISingleGirderLineFactory_ServerInfo,
    23,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISimpleGirderLineFactory, ver. 0.0,
   GUID={0x4DCF9E5C,0x3035,0x4150,{0x88,0x2E,0x70,0x84,0x79,0x6B,0x93,0xB5}} */

#pragma code_seg(".orpc")
static const unsigned short ISimpleGirderLineFactory_FormatStringOffsetTable[] =
    {
    2572,
    1470,
    1262,
    1964,
    2002,
    2040,
    228,
    2078,
    2116,
    2154,
    2692,
    2730,
    2768,
    2806,
    3072,
    3110,
    3148,
    3186,
    3224,
    3262,
    3300,
    3338,
    3376,
    3414,
    3452,
    3490,
    3528,
    3566,
    3604,
    3642
    };

static const MIDL_STUBLESS_PROXY_INFO ISimpleGirderLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISimpleGirderLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleGirderLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(33) _ISimpleGirderLineFactoryProxyVtbl = 
{
    &ISimpleGirderLineFactory_ProxyInfo,
    &IID_ISimpleGirderLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IGirderLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_GirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_GirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_GirderLineIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_GirderLineIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_LeftLayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_LeftLayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_RightLayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_RightLayoutLineID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_LayoutLineIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_LayoutLineIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_Type */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_Type */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_StartPierID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_StartPierID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_EndPierID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_EndPierID */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_PierIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_PierIDInc */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_Continuous */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_Continuous */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_StartMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_StartMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_StartMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_StartMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_EndMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_EndMeasurementType */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::get_EndMeasurementLocation */ ,
    (void *) (INT_PTR) -1 /* ISimpleGirderLineFactory::put_EndMeasurementLocation */
};

const CInterfaceStubVtbl _ISimpleGirderLineFactoryStubVtbl =
{
    &IID_ISimpleGirderLineFactory,
    &ISimpleGirderLineFactory_ServerInfo,
    33,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IGirderLine, ver. 0.0,
   GUID={0xEDD54A64,0x4F63,0x4DC0,{0xB6,0x05,0xDA,0xA4,0xC6,0x3B,0xDA,0x64}} */

#pragma code_seg(".orpc")
static const unsigned short IGirderLine_FormatStringOffsetTable[] =
    {
    0,
    3680,
    3718,
    3756,
    3794,
    3832,
    3870,
    3914,
    3958,
    4002,
    4070,
    4108,
    4146,
    518
    };

static const MIDL_STUBLESS_PROXY_INFO IGirderLine_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IGirderLine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IGirderLine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IGirderLine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IGirderLineProxyVtbl = 
{
    &IGirderLine_ProxyInfo,
    &IID_IGirderLine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_ID */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_StartPier */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_EndPier */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_GirderLength */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_SpanLength */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_LayoutLength */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_PierPoint */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_BearingPoint */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_EndPoint */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::GetEndPoints */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_Path */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_Direction */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_BearingOffset */ ,
    (void *) (INT_PTR) -1 /* IGirderLine::get_EndDistance */
};

const CInterfaceStubVtbl _IGirderLineStubVtbl =
{
    &IID_IGirderLine,
    &IGirderLine_ServerInfo,
    17,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDiaphragmLineFactory, ver. 0.0,
   GUID={0xB3979762,0xE72A,0x401B,{0xAC,0x03,0x28,0xE9,0x53,0xA2,0x22,0xC2}} */

#pragma code_seg(".orpc")
static const unsigned short IDiaphragmLineFactory_FormatStringOffsetTable[] =
    {
    4190,
    1470
    };

static const MIDL_STUBLESS_PROXY_INFO IDiaphragmLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDiaphragmLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IDiaphragmLineFactoryProxyVtbl = 
{
    &IDiaphragmLineFactory_ProxyInfo,
    &IID_IDiaphragmLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Reset */
};

const CInterfaceStubVtbl _IDiaphragmLineFactoryStubVtbl =
{
    &IID_IDiaphragmLineFactory,
    &IDiaphragmLineFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISingleDiaphragmLineFactory, ver. 0.0,
   GUID={0x56FB1927,0xB2C5,0x46AB,{0xAB,0xCC,0xDF,0x68,0xC6,0x19,0x16,0x0C}} */

#pragma code_seg(".orpc")
static const unsigned short ISingleDiaphragmLineFactory_FormatStringOffsetTable[] =
    {
    4190,
    1470,
    1502,
    1540,
    4234,
    3832,
    4272,
    4310,
    2116,
    2154,
    4348,
    4386,
    4424,
    4462,
    4500,
    4538
    };

static const MIDL_STUBLESS_PROXY_INFO ISingleDiaphragmLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISingleDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISingleDiaphragmLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISingleDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(19) _ISingleDiaphragmLineFactoryProxyVtbl = 
{
    &ISingleDiaphragmLineFactory_ProxyInfo,
    &IID_ISingleDiaphragmLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_Station */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_Station */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_Orientation */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_Orientation */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_Staggered */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_Staggered */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::put_RightGirderLineID */ ,
    (void *) (INT_PTR) -1 /* ISingleDiaphragmLineFactory::get_RightGirderLineID */
};

const CInterfaceStubVtbl _ISingleDiaphragmLineFactoryStubVtbl =
{
    &IID_ISingleDiaphragmLineFactory,
    &ISingleDiaphragmLineFactory_ServerInfo,
    19,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IThroughPointDiaphragmLineFactory, ver. 0.0,
   GUID={0xE479B523,0x613F,0x4383,{0xB5,0x55,0x2E,0x74,0x9C,0xAF,0xAB,0xE8}} */

#pragma code_seg(".orpc")
static const unsigned short IThroughPointDiaphragmLineFactory_FormatStringOffsetTable[] =
    {
    4190,
    1470,
    4576,
    4614,
    4652,
    4690,
    228,
    2078,
    4728,
    4766,
    4804,
    4842,
    4424,
    4462
    };

static const MIDL_STUBLESS_PROXY_INFO IThroughPointDiaphragmLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IThroughPointDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IThroughPointDiaphragmLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IThroughPointDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(17) _IThroughPointDiaphragmLineFactoryProxyVtbl = 
{
    &IThroughPointDiaphragmLineFactory_ProxyInfo,
    &IID_IThroughPointDiaphragmLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_Point */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_Point */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_Direction */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_Direction */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_Staggered */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_Staggered */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::put_RightGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IThroughPointDiaphragmLineFactory::get_RightGirderLineID */
};

const CInterfaceStubVtbl _IThroughPointDiaphragmLineFactoryStubVtbl =
{
    &IID_IThroughPointDiaphragmLineFactory,
    &IThroughPointDiaphragmLineFactory_ServerInfo,
    17,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IEqualSpaceDiaphragmLineFactory, ver. 0.0,
   GUID={0xFD9086BA,0x9DEA,0x4AF0,{0xBD,0xF9,0x5E,0x67,0xE7,0xE0,0xA1,0xD0}} */

#pragma code_seg(".orpc")
static const unsigned short IEqualSpaceDiaphragmLineFactory_FormatStringOffsetTable[] =
    {
    4190,
    1470,
    1502,
    1540,
    4234,
    3832,
    4880,
    4918,
    2116,
    2154,
    2692,
    2730,
    4956,
    4994,
    5032,
    5070,
    5108,
    5146,
    2420,
    2458
    };

static const MIDL_STUBLESS_PROXY_INFO IEqualSpaceDiaphragmLineFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IEqualSpaceDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IEqualSpaceDiaphragmLineFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IEqualSpaceDiaphragmLineFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(23) _IEqualSpaceDiaphragmLineFactoryProxyVtbl = 
{
    &IEqualSpaceDiaphragmLineFactory_ProxyInfo,
    &IID_IEqualSpaceDiaphragmLineFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLineFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_AlignmentID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_StartStation */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_StartStation */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_EndStation */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_EndStation */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_DiaphragmLineID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_DiaphragmLineIDInc */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_DiaphragmLineIDInc */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_Divisor */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_Divisor */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_Staggered */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_Staggered */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_LeftGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::put_RightGirderLineID */ ,
    (void *) (INT_PTR) -1 /* IEqualSpaceDiaphragmLineFactory::get_RightGirderLineID */
};

const CInterfaceStubVtbl _IEqualSpaceDiaphragmLineFactoryStubVtbl =
{
    &IID_IEqualSpaceDiaphragmLineFactory,
    &IEqualSpaceDiaphragmLineFactory_ServerInfo,
    23,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDiaphragmLine, ver. 0.0,
   GUID={0x24885559,0xFABB,0x4327,{0xB3,0x0D,0xB2,0xEE,0x5C,0x95,0xC5,0xC1}} */

#pragma code_seg(".orpc")
static const unsigned short IDiaphragmLine_FormatStringOffsetTable[] =
    {
    0,
    5184,
    5228
    };

static const MIDL_STUBLESS_PROXY_INFO IDiaphragmLine_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDiaphragmLine_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDiaphragmLine_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDiaphragmLine_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IDiaphragmLineProxyVtbl = 
{
    &IDiaphragmLine_ProxyInfo,
    &IID_IDiaphragmLine,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDiaphragmLine::get_ID */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLine::get_Length */ ,
    (void *) (INT_PTR) -1 /* IDiaphragmLine::get_Point */
};

const CInterfaceStubVtbl _IDiaphragmLineStubVtbl =
{
    &IID_IDiaphragmLine,
    &IDiaphragmLine_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDeckBoundary, ver. 0.0,
   GUID={0x8FC6DE2C,0x969D,0x4F74,{0xBD,0x77,0x93,0x55,0xC1,0xC4,0xBE,0xB6}} */

#pragma code_seg(".orpc")
static const unsigned short IDeckBoundary_FormatStringOffsetTable[] =
    {
    5278,
    5322,
    5378,
    5440
    };

static const MIDL_STUBLESS_PROXY_INFO IDeckBoundary_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDeckBoundary_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDeckBoundary_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDeckBoundary_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IDeckBoundaryProxyVtbl = 
{
    &IDeckBoundary_ProxyInfo,
    &IID_IDeckBoundary,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDeckBoundary::get_Perimeter */ ,
    (void *) (INT_PTR) -1 /* IDeckBoundary::get_PerimeterEx */ ,
    (void *) (INT_PTR) -1 /* IDeckBoundary::get_TransverseEdgePoints */ ,
    (void *) (INT_PTR) -1 /* IDeckBoundary::get_EdgePath */
};

const CInterfaceStubVtbl _IDeckBoundaryStubVtbl =
{
    &IID_IDeckBoundary,
    &IDeckBoundary_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDeckBoundaryFactory, ver. 0.0,
   GUID={0xF89D246A,0x8F7D,0x4A27,{0xA2,0x7E,0xDD,0x73,0xBE,0x33,0x20,0x87}} */

#pragma code_seg(".orpc")
static const unsigned short IDeckBoundaryFactory_FormatStringOffsetTable[] =
    {
    5490,
    1470
    };

static const MIDL_STUBLESS_PROXY_INFO IDeckBoundaryFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDeckBoundaryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IDeckBoundaryFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IDeckBoundaryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IDeckBoundaryFactoryProxyVtbl = 
{
    &IDeckBoundaryFactory_ProxyInfo,
    &IID_IDeckBoundaryFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDeckBoundaryFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDeckBoundaryFactory::Reset */
};

const CInterfaceStubVtbl _IDeckBoundaryFactoryStubVtbl =
{
    &IID_IDeckBoundaryFactory,
    &IDeckBoundaryFactory_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ISimpleDeckBoundaryFactory, ver. 0.0,
   GUID={0xAA59EF93,0x7A3C,0x493A,{0xBF,0x37,0xB3,0x8B,0x36,0x44,0xA6,0x53}} */

#pragma code_seg(".orpc")
static const unsigned short ISimpleDeckBoundaryFactory_FormatStringOffsetTable[] =
    {
    5490,
    1470,
    5534,
    5578,
    5622,
    5666,
    5710,
    5754,
    5798,
    5842,
    5886,
    5936
    };

static const MIDL_STUBLESS_PROXY_INFO ISimpleDeckBoundaryFactory_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleDeckBoundaryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ISimpleDeckBoundaryFactory_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &ISimpleDeckBoundaryFactory_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _ISimpleDeckBoundaryFactoryProxyVtbl = 
{
    &ISimpleDeckBoundaryFactory_ProxyInfo,
    &IID_ISimpleDeckBoundaryFactory,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IDeckBoundaryFactory::Create */ ,
    (void *) (INT_PTR) -1 /* IDeckBoundaryFactory::Reset */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::put_TransverseEdgeID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::get_TransverseEdgeID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::put_TransverseEdgeType */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::get_TransverseEdgeType */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::put_EdgeID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::get_EdgeID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::put_EdgeBreakID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::get_EdgeBreakID */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::put_BreakEdge */ ,
    (void *) (INT_PTR) -1 /* ISimpleDeckBoundaryFactory::get_BreakEdge */
};

const CInterfaceStubVtbl _ISimpleDeckBoundaryFactoryStubVtbl =
{
    &IID_ISimpleDeckBoundaryFactory,
    &ISimpleDeckBoundaryFactory_ServerInfo,
    15,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IBridgeGeometry, ver. 0.0,
   GUID={0xCF09FA44,0x1095,0x4F63,{0xB3,0xDB,0xC4,0xBA,0x86,0x17,0xA9,0x8E}} */

#pragma code_seg(".orpc")
static const unsigned short IBridgeGeometry_FormatStringOffsetTable[] =
    {
    5986,
    6024,
    6062,
    6106,
    1578,
    190,
    6150,
    6188,
    1692,
    6226,
    6264,
    6302,
    1844,
    6346,
    6420,
    6464,
    3148,
    6508,
    6546,
    2458,
    6590,
    6628,
    6672,
    6710,
    6748,
    6786
    };

static const MIDL_STUBLESS_PROXY_INFO IBridgeGeometry_ProxyInfo =
    {
    &Object_StubDesc,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IBridgeGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IBridgeGeometry_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    WBFLBridgeGeometry__MIDL_ProcFormatString.Format,
    &IBridgeGeometry_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(29) _IBridgeGeometryProxyVtbl = 
{
    &IBridgeGeometry_ProxyInfo,
    &IID_IBridgeGeometry,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::putref_CogoModel */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_CogoModel */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::putref_Alignment */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_Alignment */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::put_BridgeAlignmentID */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_BridgeAlignmentID */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_BridgeAlignment */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::put_AlignmentOffset */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_AlignmentOffset */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_BridgeLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::CreateLayoutLines */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::FindLayoutLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_LayoutLineCount */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::CreatePierLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::GetPierLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::FindPierLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_PierLineCount */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::CreateGirderLines */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::FindGirderLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_GirderLineCount */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::CreateDiaphragmLines */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::FindDiaphragmLine */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_DiaphragmLineCount */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::CreateDeckBoundary */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::get_DeckBoundary */ ,
    (void *) (INT_PTR) -1 /* IBridgeGeometry::UpdateGeometry */
};

const CInterfaceStubVtbl _IBridgeGeometryStubVtbl =
{
    &IID_IBridgeGeometry,
    &IBridgeGeometry_ServerInfo,
    29,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    WBFLBridgeGeometry__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _WBFLBridgeGeometry_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IThroughPointDiaphragmLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ILayoutLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IUniformSpacingLayoutLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISingleDiaphragmLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDeckBoundaryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IBridgeGeometryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDiaphragmLineProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISimpleGirderLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDiaphragmLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAlignmentOffsetLayoutLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGirderLineProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDeckBoundaryFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPierLineProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISingleGirderLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IGirderLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISimpleLayoutLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ISimpleDeckBoundaryFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IEqualSpaceDiaphragmLineFactoryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPierLineCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IEnumPierLinesProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _WBFLBridgeGeometry_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IThroughPointDiaphragmLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ILayoutLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IUniformSpacingLayoutLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ISingleDiaphragmLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IDeckBoundaryStubVtbl,
    ( CInterfaceStubVtbl *) &_IBridgeGeometryStubVtbl,
    ( CInterfaceStubVtbl *) &_IDiaphragmLineStubVtbl,
    ( CInterfaceStubVtbl *) &_ISimpleGirderLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IDiaphragmLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IAlignmentOffsetLayoutLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IGirderLineStubVtbl,
    ( CInterfaceStubVtbl *) &_IDeckBoundaryFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IPierLineStubVtbl,
    ( CInterfaceStubVtbl *) &_ISingleGirderLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IGirderLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ISimpleLayoutLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_ISimpleDeckBoundaryFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IEqualSpaceDiaphragmLineFactoryStubVtbl,
    ( CInterfaceStubVtbl *) &_IPierLineCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IEnumPierLinesStubVtbl,
    0
};

PCInterfaceName const _WBFLBridgeGeometry_InterfaceNamesList[] = 
{
    "IThroughPointDiaphragmLineFactory",
    "ILayoutLineFactory",
    "IUniformSpacingLayoutLineFactory",
    "ISingleDiaphragmLineFactory",
    "IDeckBoundary",
    "IBridgeGeometry",
    "IDiaphragmLine",
    "ISimpleGirderLineFactory",
    "IDiaphragmLineFactory",
    "IAlignmentOffsetLayoutLineFactory",
    "IGirderLine",
    "IDeckBoundaryFactory",
    "IPierLine",
    "ISingleGirderLineFactory",
    "IGirderLineFactory",
    "ISimpleLayoutLineFactory",
    "ISimpleDeckBoundaryFactory",
    "IEqualSpaceDiaphragmLineFactory",
    "IPierLineCollection",
    "IEnumPierLines",
    0
};


#define _WBFLBridgeGeometry_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _WBFLBridgeGeometry, pIID, n)

int __stdcall _WBFLBridgeGeometry_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _WBFLBridgeGeometry, 20, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _WBFLBridgeGeometry, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _WBFLBridgeGeometry, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _WBFLBridgeGeometry, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _WBFLBridgeGeometry, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _WBFLBridgeGeometry, 20, *pIndex )
    
}

const ExtendedProxyFileInfo WBFLBridgeGeometry_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _WBFLBridgeGeometry_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _WBFLBridgeGeometry_StubVtblList,
    (const PCInterfaceName * ) & _WBFLBridgeGeometry_InterfaceNamesList,
    0, /* no delegation */
    & _WBFLBridgeGeometry_IID_Lookup, 
    20,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

