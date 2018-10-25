

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 30 08:02:27 2017
 */
/* Compiler settings for ..\Include\WBFLTypes.idl:
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


#ifndef ___WBFLTypes_h__
#define ___WBFLTypes_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "basetsd.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WBFLTypes_0000_0000 */
/* [local] */ 

#define LUMP_STRANDS
#if _WIN32_WINNT < 0x0600
#define MAXUINT64   ((UINT64)~((UINT64)0))
#define MAXUINT32   ((UINT32)~((UINT32)0))
#define MAXINT16    ((INT16)(MAXUINT16 >> 1))
#define MAXINT32    ((INT32)(MAXUINT32 >> 1))
#define MAXINT64    ((INT64)(MAXUINT64 >> 1))
#endif
#if defined UNICODE || defined _UNICODE
#define _tstring wstring
#define _tstringstream wstringstream 
#define _tostringstream wostringstream 
#define _tistringstream wistringstream 
#define _tifstream wifstream
#define _tofstream wofstream
#define _tostream wostream
#define _tistream wistream
#define _tcout wcout
#define _tcin wcin
#else
#define _tstring string
#define _tstringstream stringstream
#define _tostringstream ostringstream
#define _tistringstream istringstream
#define _tifstream ifstream
#define _tofstream ofstream
#define _tostream ostream
#define _tistream istream
#define _tcout cout
#define _tcin cin
#endif
#include <limits.h>
#include <float.h>
typedef        char    Int8;
typedef long double Float80;
#define Int8_Max      SCHAR_MAX
#define Int8_Min      SCHAR_MIN
#define Int16_Max     SHRT_MAX
#define Int16_Min     SHRT_MIN
#define Int32_Max     LONG_MAX
#define Int32_Min     LONG_MIN
#define Int64_Max     LLONG_MAX
#define Int64_Min     LLONG_MIN
#define Uint8_Max     UCHAR_MAX
#define Uint16_Max    USHRT_MAX
#define Uint32_Max    ULONG_MAX
#define Uint64_Max    ULLONG_MAX
#define Float32_Max   FLT_MAX
#define Float32_Min   FLT_MIN
#define Float32_Inf   std::numeric_limits<Float32>::infinity()
#define Float64_Max   DBL_MAX
#define Float64_Inf   std::numeric_limits<Float64>::infinity()
#define Float64_Min   DBL_MIN
#define Float80_Max   LDBL_MAX
#define Float80_Min   LDBL_MIN
typedef short Int16;

typedef INT32 Int32;

typedef unsigned char Uint8;

typedef unsigned short Uint16;

typedef UINT32 Uint32;

typedef INT64 Int64;

typedef UINT64 Uint64;

typedef float Float32;

typedef double Float64;

typedef INT64 IDType;

#define INVALID_ID -1
#define MAX_ID MAXINT64
#define VARIANT2ID(_var_) _var_.llVal
#define VT_ID VT_I8
typedef IDType SpanIDType;

typedef IDType PierIDType;

typedef IDType JointIDType;

typedef IDType MemberIDType;

typedef IDType SupportIDType;

typedef IDType LoadIDType;

typedef IDType PoiIDType;

typedef IDType LoadCaseIDType;

typedef IDType LoadGroupIDType;

typedef IDType LoadCombinationIDType;

typedef IDType GirderIDType;

typedef IDType GroupIDType;

typedef IDType SegmentIDType;

typedef IDType ClosureIDType;

typedef IDType StageIDType;

typedef IDType EventIDType;

typedef Int32 BarSizeType;

typedef UINT64 IndexType;

#define MAX_INDEX (MAXUINT64-1)
#define INVALID_INDEX (MAX_INDEX+1)
#define VARIANT2INDEX(_var_) _var_.ullVal
#define VT_INDEX VT_UI8
#define FIXED_AXLE_TRUCK INVALID_INDEX
#define ALL_SPANS        INVALID_INDEX
#define ALL_PIERS        INVALID_INDEX
#define ALL_GIRDERS      INVALID_INDEX
#define ALL_GROUPS       INVALID_INDEX
#define ALL_SEGMENTS     INVALID_INDEX
#define ALL_STAGES       INVALID_INDEX
#define ALL_DUCTS        INVALID_INDEX
#define INVALID_BAR_SIZE INVALID_INDEX
typedef IndexType CollectionIndexType;

typedef IndexType StageIndexType;

typedef IndexType EventIndexType;

typedef IndexType SupportIndexType;

typedef IndexType StrandIndexType;

typedef IndexType SpanIndexType;

typedef IndexType GirderIndexType;

typedef IndexType PierIndexType;

typedef IndexType ColumnIndexType;

typedef IndexType GroupIndexType;

typedef IndexType SpacingIndexType;

typedef IndexType VehicleIndexType;

typedef IndexType AxleIndexType;

typedef IndexType GridIndexType;

typedef IndexType SectionIndexType;

typedef IndexType RowIndexType;

typedef IndexType SegmentIndexType;

typedef IndexType MatingSurfaceIndexType;

typedef IndexType WebIndexType;

typedef IndexType FlangeIndexType;

typedef IndexType SplittingPlaneIndexType;

typedef IndexType ZoneIndexType;

typedef IndexType DuctIndexType;

typedef IndexType IntervalIndexType;

typedef Int64 SpanGirderHashType;
typedef Int64 PierGirderHashType;
inline Uint16 make_Uint16(Uint8  lo, Uint8  hi) {return (Uint16)(lo & 0xFF)  | (Uint16)(hi & 0xFF) << 8;}
inline Int16  make_Int16 (Int8   lo, Int8   hi) {return (Int16)(lo  & 0xFF) | (Int16) (hi & 0xFF)  << 8;}
inline Uint32 make_Uint32(Uint16 lo, Uint16 hi) {return (Uint32)(lo & 0xFFFF) | (Uint32)(hi & 0xFFFF) << 16;}
inline Int32  make_Int32 (Int16  lo, Int16  hi) {return (Int32)( lo & 0xFFFF) | (Int32)( hi & 0xFFFF) << 16;}
inline Uint16 low_Uint16(Uint32 u32) {return u32 & 0xFF;}
inline Int16  low_Int16(Int32 u32)   {return u32 & 0xFF;}
inline Uint16 high_Uint16(Uint32 u32) {  return u32 >> 16;}
inline Int16  high_Int16(Uint32 u32)  {  return u32 >> 16;}
inline Uint8 low_Uint8(Uint16 u16){ return u16 & 0xFF;}
inline Int8  low_Int8(Uint16 u16) { return u16 & 0xFF;}
inline Uint8 high_Uint8(Uint16 u16) { return u16 >> 8;}
inline Int8  high_Int8(Uint16 u16)  { return u16 >> 8;}
inline Uint64 make_Uint64(Uint32  lo, Uint32  hi) {return (Uint64)(lo &  0xFFFFFFFF) | (Uint64)( hi &  0xFFFFFFFF) << 32;}
inline Uint32 low_Uint32(Uint64 u64) {return u64 & 0xFFFFFFFF;}
inline Uint32 high_Uint32(Uint64 u64) {return u64 >> 32;}
inline Int64 make_Int64 (Int32  lo, Int32  hi) {return (Int64)(lo &  0xFFFFFFFF) | (Int64)( hi &  0xFFFFFFFF) << 32;}
inline Int32 low_Int32(Int64 u64) {return u64 & 0xFFFFFFFF;}
inline Int32 high_Int32(Int64 u64) {return u64 >> 32;}
inline SpanGirderHashType HashSpanGirder(SpanIndexType span,GirderIndexType girder) { return make_Int64((Int32)span,(Int32)girder); }
inline void UnhashSpanGirder(SpanGirderHashType hash,SpanIndexType* span,GirderIndexType* girder) { *span =  low_Int32(hash); *girder = high_Int32(hash); }
inline PierGirderHashType HashPierGirder(PierIndexType pier,GirderIndexType girder) { return make_Int64((Int32)pier,(Int32)girder); }
inline void UnhashPierGirder(PierGirderHashType hash,PierIndexType* pier,GirderIndexType* girder) { *pier =  low_Int32(hash); *girder = high_Int32(hash); }


extern RPC_IF_HANDLE __MIDL_itf_WBFLTypes_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WBFLTypes_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


